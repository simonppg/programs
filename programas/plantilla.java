package innovatissolution.domotica;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;

import org.json.JSONException;

import com.markupartist.android.widget.ActionBar;
import com.markupartist.android.widget.ActionBar.AbstractAction;
import com.markupartist.android.widget.ActionBar.IntentAction;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.Window;
import android.view.View.OnClickListener;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.ToggleButton;


public class "Nombre_del_lugar" extends Activity {
	private final int ON = 1;
	private final int OFF = 0;

	private ImageView imgPhoto;
	private Bitmap bmp;
	private Handler mHandler;
	private Conectar conector;
	private String datos;
	private TextView LabTemp;

	private TextView LabPres;

	"numero_de_focos"
	private int int_foco"1";
	private int int_foco"2";
	private String E_foco"1";
	private String E_foco"2";
	private int S_foco"1";
	private int S_foco"2";

	"numeo_de_aires"
	private int int_aire"1";
	private String E_aire"1";
	private int S_aire"1";

	private int S_temp;
	private int S_pres1;
	private ArrayList<String> AL_temp;
	private ArrayList<String> AL_pres;
	private ArrayList<String> AL_aire;
	private ArrayList<String> AL_aire1E;
	private ArrayList<String> AL_luz;
	private ArrayList<String> AL_foco1E;
	private ToggleButton TogFoco1;
	private ToggleButton TogAire1;
	
	private static String RUTA="/innovatiss/";
	private static String FILE="Nombre_del_lugar.png";











































