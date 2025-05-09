package com.taskrabbit.zendesk;

import android.app.Activity;
import android.app.Application;
import android.os.Bundle;

class RNZendeskActivityTracker implements Application.ActivityLifecycleCallbacks {
	private static Activity currentActivity;

	@Override
	public void onActivityResumed(Activity activity) {
		currentActivity = activity;
	}

	@Override
	public void onActivityPaused(Activity activity) {
		if (currentActivity == activity) currentActivity = null;
	}

	public static Activity getCurrentActivity() {
		return currentActivity;
	}

	// Implement other lifecycle methods as no-ops
	@Override public void onActivityCreated(Activity a, Bundle b) {}
	@Override public void onActivityStarted(Activity a) {}
	@Override public void onActivityStopped(Activity a) {}
	@Override public void onActivitySaveInstanceState(Activity a, Bundle b) {}
	@Override public void onActivityDestroyed(Activity a) {}
}
