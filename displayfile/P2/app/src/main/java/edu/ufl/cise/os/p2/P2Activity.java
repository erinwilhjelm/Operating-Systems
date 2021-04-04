package edu.ufl.cise.os.p2;

import android.os.Bundle;
import android.widget.TextView;
import android.app.Activity;
import android.widget.Button;
import android.widget.EditText;
import android.view.View;
import android.view.View.OnClickListener;



public class P2Activity extends Activity {


    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    private EditText filenameBox;
    private Button submitButton;
    private TextView tv;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_p2);



        submitButton = findViewById(R.id.submitButton);
        filenameBox = findViewById(R.id.filenameBox);
        tv = findViewById(R.id.displayBox);


        submitButton.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View view) {

                String path = String.valueOf(filenameBox.getText());



                tv.setText(stringFromJNI(path));


            }
        });
    }





    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */

    public native String stringFromJNI(String path);
}
