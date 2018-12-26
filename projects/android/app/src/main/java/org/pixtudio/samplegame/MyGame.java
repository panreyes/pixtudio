package org.libsdl.app;

import org.libsdl.app.SDLActivity;
import android.os.Bundle;
import android.content.*;
import android.net.Uri;

/*
 * A sample wrapper class that just calls SDLActivity
 */

public class MyGame extends SDLActivity {
    // Taken from
    // http://digitalsynapsesblog.blogspot.com.es/2011/09/cocos2d-x-launching-url-on-android.html
    public static void openURL(String url) {
        Intent i = new Intent(Intent.ACTION_VIEW);
        i.setData(Uri.parse(url));
        mSingleton.startActivity(i);
    }
}
