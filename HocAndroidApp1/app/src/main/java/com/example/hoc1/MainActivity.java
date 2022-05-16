package com.example.hoc1;

import androidx.appcompat.app.AppCompatActivity;

import android.os.AsyncTask;
import android.os.Bundle;
import android.view.View;
import android.widget.CompoundButton;
import android.widget.Switch;
import android.widget.TextView;

import com.android.volley.AuthFailureError;
import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.JsonObjectRequest;
import com.android.volley.toolbox.StringRequest;
import com.android.volley.toolbox.Volley;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.Console;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;


public class MainActivity extends AppCompatActivity {
    private String gateUrl ="https://dtipsstore.table.core.windows.net/gate(PartitionKey='gate',RowKey='state')?sv=";
    private boolean isOpen = false;

    private Switch onOffSwitch= null;
    private boolean suppressClick = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        UpdateGateStatus();

        onOffSwitch = (Switch)  findViewById(R.id.buttonGateOpen);
        onOffSwitch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {

            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if(suppressClick)return;
                OpenGate(buttonView);
            }

        });

    }



    public void OpenGate(View view) {

        // Instantiate the RequestQueue.
        RequestQueue queue = Volley.newRequestQueue(this);
        String request=  "{\"Open\":"+!isOpen+"}";

        // Request a string response from the provided URL.
        StringRequest stringRequest = new StringRequest(Request.Method.PUT, gateUrl,
                new Response.Listener<String>() {
                    @Override
                    public void onResponse(String response) {
                        // Display the first 500 characters of the response string.
                        UpdateGateStatus();
                    }
                }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                UpdateGateStatus();
            }
        }){
            @Override
            public byte[] getBody() throws AuthFailureError {
                return request.getBytes();
            }
            public Map<String,String> getHeaders() throws AuthFailureError {
                Map<String, String> params = new HashMap<String, String>();
                params.put("Content-Type", "application/json");
                params.put("Accept", "application/json");
                return params;
            }
        };


        // Add the request to the RequestQueue.
        queue.add(stringRequest);

    }

    private void UpdateGateStatus() {
        TextView label = (TextView)findViewById(R.id.GateStatus);

        // Instantiate the RequestQueue.
        RequestQueue queue = Volley.newRequestQueue(this);


        // Request a string response from the provided URL.
        JsonObjectRequest jsonObjectRequest = new JsonObjectRequest(Request.Method.GET, gateUrl,null , new Response.Listener<JSONObject>() {

                    @Override
                    public void onResponse(JSONObject response) {
                        try {
                            if(response.get("Open").toString()=="true"){
                                label.setText("open");
                                isOpen= true;
                            }
                            else{
                                label.setText("closed");
                                isOpen= false;
                            }
                        } catch (JSONException e) {
                            e.printStackTrace();
                        }finally {
                            suppressClick= true;
                            onOffSwitch.setChecked(isOpen);
                            suppressClick = false;
                        }
                        // Display the first 500 characters of the response string.
                       // textView.setText("Response is: "+ response.substring(0,500));
                    }
                }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {
                TextView label = (TextView)findViewById(R.id.GateStatus);
                label.setText("Error, Something is wrong.");
            }
        }){
            @Override
            public Map<String,String> getHeaders() throws AuthFailureError {
                Map<String, String> params = new HashMap<String, String>();
                params.put("Accept", "application/json");
                return params;
            }
        };

        // Add the request to the RequestQueue.

        queue.add(jsonObjectRequest);
    }

}
