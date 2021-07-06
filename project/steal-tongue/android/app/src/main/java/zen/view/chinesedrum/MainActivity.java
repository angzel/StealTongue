package zen.view.chinesedrum;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;
import zen.utils.*;
import zen.app.*;

public class MainActivity extends zen.app.AppActivity {

	// Used to load the 'native-lib' library on application startup.
	static {
		System.loadLibrary("native-lib");
	}

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		zen.utils.Utils.initialize(this);

	}
}