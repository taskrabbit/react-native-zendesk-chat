package com.taskrabbit.zendesk;

import com.facebook.react.bridge.ReadableMap;

import org.json.JSONObject;

import java.nio.charset.StandardCharsets;
import java.util.Map;

import okhttp3.HttpUrl;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.RequestBody;
import okhttp3.Response;
import zendesk.chat.JwtAuthenticator;

public class RNZendeskJwtAuthenticationModule implements JwtAuthenticator {
    private String m_tokenEndpoint;
    private String m_externalId;
    private String m_prefetchedJwt;
    private ReadableMap m_extraHeaders;
    private OkHttpClient m_httpClient = new OkHttpClient();

    RNZendeskJwtAuthenticationModule(ReadableMap options) {
        super();

        String prefetchedJwt = options.getString("jwt");

        if (prefetchedJwt != null) {
            this.m_prefetchedJwt = prefetchedJwt;
        } else {
            this.m_externalId = options.getString("externalId");
            this.m_tokenEndpoint = options.getString("tokenEndpoint");
            this.m_extraHeaders = options.getMap("headers");
        }
    }

    @Override
    public void getToken(JwtCompletion jwtCompletion) {
        if (this.m_prefetchedJwt != null) {
            jwtCompletion.onTokenLoaded(this.m_prefetchedJwt);
        } else {
            this.makeHttpRequest(jwtCompletion);
        }
    }

    public boolean canUseJwtAuth() {
        return this.m_prefetchedJwt != null || (this.m_tokenEndpoint != null && this.m_externalId != null);
    }

    private void makeHttpRequest(JwtCompletion completion) {
        RequestBody body = RequestBody.create(this.getTokenRequestJson());

        Request.Builder builder = new Request.Builder()
            .post(body)
            .url(HttpUrl.get(this.m_tokenEndpoint))
            .header("Content-Type", "application/json");

        this.applyCustomerHeaders(builder);

        Request request = builder.build();

        try {
            Response response = this.m_httpClient.newCall(request).execute();

            JSONObject responseObject = new JSONObject(response.body().string());

            String jwt = responseObject.getString("jwt");

            if (jwt != null) {
                completion.onTokenLoaded(jwt);
            }

            completion.onError();
        } catch (Exception ex) {
            completion.onError();
        }
    }

    private void applyCustomerHeaders(Request.Builder builder) {
        if (this.m_extraHeaders == null) {
            return;
        }

        for (Map.Entry<String, Object> entry: this.m_extraHeaders.toHashMap().entrySet()) {
            builder.header(entry.getKey(), entry.getValue().toString());
        }
    }

    private byte[] getTokenRequestJson() {
        try {
            JSONObject json = new JSONObject();

            json.put("externalId", this.m_externalId);

            return json.toString().getBytes(StandardCharsets.UTF_8);
        } catch (Exception exception) {
            return "{}".getBytes(StandardCharsets.UTF_8);
        }
    }
}