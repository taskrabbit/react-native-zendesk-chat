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
    private String mTokenEndpoint;
    private String mExternalId;
    private String mPrefetchedJwt;
    private ReadableMap mExtraHeaders;
    private OkHttpClient mHttpClient = new OkHttpClient();

    RNZendeskJwtAuthenticationModule(ReadableMap options) {
        super();

        String prefetchedJwt = options.getString("jwt");

        if (prefetchedJwt != null) {
            this.mPrefetchedJwt = prefetchedJwt;
        } else {
            this.mExternalId = options.getString("externalId");
            this.mTokenEndpoint = options.getString("tokenEndpoint");
            this.mExtraHeaders = options.getMap("headers");
        }
    }

    @Override
    public void getToken(JwtCompletion jwtCompletion) {
        if (this.mPrefetchedJwt != null) {
            jwtCompletion.onTokenLoaded(this.mPrefetchedJwt);
        } else {
            this.makeHttpRequest(jwtCompletion);
        }
    }

    public boolean canUseJwtAuth() {
        return this.mPrefetchedJwt != null || (this.mTokenEndpoint != null && this.mExternalId != null);
    }

    private void makeHttpRequest(JwtCompletion completion) {
        RequestBody body = RequestBody.create(this.getTokenRequestJson());

        Request.Builder builder = new Request.Builder()
            .post(body)
            .url(HttpUrl.get(this.mTokenEndpoint))
            .header("Content-Type", "application/json");

        this.applyCustomerHeaders(builder);

        Request request = builder.build();

        try {
            Response response = this.mHttpClient.newCall(request).execute();

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
        if (this.mExtraHeaders == null) {
            return;
        }

        for (Map.Entry<String, Object> entry: this.mExtraHeaders.toHashMap().entrySet()) {
            builder.header(entry.getKey(), entry.getValue().toString());
        }
    }

    private byte[] getTokenRequestJson() {
        try {
            JSONObject json = new JSONObject();

            json.put("externalId", this.mExternalId);

            return json.toString().getBytes(StandardCharsets.UTF_8);
        } catch (Exception exception) {
            return "{}".getBytes(StandardCharsets.UTF_8);
        }
    }
}