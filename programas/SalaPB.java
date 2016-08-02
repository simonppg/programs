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

public class SalaPB extends Activity {
	private final int ON = 1;
	private final int OFF = 0;

	private ImageView imgPhoto;
	private Bitmap bmp;
	private Handler mHandler;
	private Conectar conector;
	private String datos;
	private TextView LabTemp;

	private TextView LabPres;
	private int int_foco1;
	private int int_aire1;
	private String E_aire1;
	private String E_foco1;
	private int S_foco1;
	private int S_aire1;
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
	private static String FILE="SalaPB.png";


	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		setContentView(R.layout.f1a1);
		ActionBar actionBar = (ActionBar) findViewById(R.id.actionbar);
		actionBar.setTitle("Sala Planta Baja");
	    //actionBar.setHomeAction(new IntentAction(this,new Intent(SalaPB.this, Principal.class), R.drawable.ic_title_home_default));
	    actionBar.setDisplayHomeAsUpEnabled(true);
	    actionBar.setHomeAction(new ExampleAction());
	    
		LabTemp = new TextView(this);
		LabTemp = (TextView) findViewById(R.id.textView5);
		imgPhoto = new ImageView(this);
		imgPhoto = (ImageView) findViewById(R.id.imageView_sala);
		LabPres = new TextView(this);
		LabPres = (TextView) findViewById(R.id.TextView02);
		TogFoco1 = new ToggleButton(this);
		TogFoco1 = (ToggleButton) findViewById(R.id.togglebutton_foco1);
		TogAire1 = new ToggleButton(this);
		TogAire1 = (ToggleButton) findViewById(R.id.togglebutton_aire1);

		TogAire1.setOnClickListener(new OnClickListener() {

			public void onClick(View v) {
				if (TogAire1.isChecked()) {
					int_aire1 = ON;
					AL_aire1E = new ArrayList<String>();
					E_aire1 = "UPDATE aire SET estado = " + int_aire1
							+ " WHERE aire.zona = 'sala_pb' and no_aire=1";
					// E_foco1="UPDATE lamparas SET estado = '1'";
					AL_aire1E.clear();
					AL_aire1E.add("Query");
					AL_aire1E.add(E_aire1);
					conector.Conectar(AL_aire1E);
				} else {
					int_aire1 = OFF;
					AL_aire1E = new ArrayList<String>();
					E_aire1 = "UPDATE aire SET estado = " + int_aire1
							+ " WHERE aire.zona = 'sala_pb' and no_aire=1";
					// E_foco1= "UPDATE lamparas SET estado = '0'";
					AL_aire1E.clear();
					AL_aire1E.add("Query");
					AL_aire1E.add(E_aire1);
					conector.Conectar(AL_aire1E);
				}

			}
		});

		TogFoco1.setOnClickListener(new OnClickListener() {
			public void onClick(View v) {
				if (TogFoco1.isChecked()) {
					int_foco1 = ON;
					AL_foco1E = new ArrayList<String>();
					E_foco1 = "UPDATE lamparas SET estado = "
							+ int_foco1
							+ " WHERE lamparas.zona = 'sala_pb' and no_sensor=1";
					// E_foco1="UPDATE lamparas SET estado = '1'";
					AL_foco1E.clear();
					AL_foco1E.add("Query");
					AL_foco1E.add(E_foco1);
					conector.Conectar(AL_foco1E);
				} else {
					int_foco1 = OFF;
					AL_foco1E = new ArrayList<String>();
					E_foco1 = "UPDATE lamparas SET estado = "
							+ int_foco1
							+ " WHERE lamparas.zona = 'sala_pb' and no_sensor=1";
					// E_foco1= "UPDATE lamparas SET estado = '0'";
					AL_foco1E.clear();
					AL_foco1E.add("Query");
					AL_foco1E.add(E_foco1);
					conector.Conectar(AL_foco1E);
				}
			}
		});

		File sd = Environment.getExternalStorageDirectory();
		File imagenPersonalizada = new File(sd, RUTA + FILE);
		if (bmp != null) {
			bmp.recycle();
			bmp = null;
			System.gc();
		}
		bmp = Scale_Image.loadBitmap(imagenPersonalizada.getAbsolutePath(),
				500, 500);

		if (imagenPersonalizada.exists())
			imgPhoto.setImageBitmap(bmp);

		// Consultas
		conector = new Conectar();
		String Q_temp = "SELECT no_sensor,estado FROM zona,temperatura  WHERE temperatura.zona = 'sala_pb' and zona.nombre = temperatura.zona";
		AL_temp = new ArrayList<String>();
		AL_temp.add("Query");
		AL_temp.add(Q_temp);
		temp(AL_temp);

		String Q_pres = "SELECT no_sensor,estado FROM zona,presencia WHERE presencia.zona = 'sala_pb' and zona.nombre = presencia.zona";
		AL_pres = new ArrayList<String>();
		AL_pres.add("Query");
		AL_pres.add(Q_pres);
		pres(AL_pres);

		String Q_luz = "SELECT no_sensor,estado FROM zona,lamparas WHERE lamparas.zona = 'sala_pb' and zona.nombre = lamparas.zona";
		AL_luz = new ArrayList<String>();
		AL_luz.add("Query");
		AL_luz.add(Q_luz);
		luz(AL_luz);

		String Q_aire = "SELECT no_aire,estado FROM zona,aire WHERE aire.zona = 'sala_pb' and zona.nombre = aire.zona";
		AL_aire = new ArrayList<String>();
		AL_aire.add("Query");
		AL_aire.add(Q_aire);
		aire(AL_aire);

		mHandler = new Handler();
		mHandler.post(espera);

	}

	private void aire(ArrayList<String> parametros) {
		conector.Conectar(parametros);
		datos = conector.getDatos();
		try {
			S_aire1 = conector.getDato("estado", 0);
		} catch (JSONException e) {
			e.printStackTrace();
		}
		if (S_aire1 == ON) {
			TogAire1.setChecked(true);
			int_aire1 = ON;
		}
		if (S_aire1 == OFF) {
			TogAire1.setChecked(false);
			int_aire1 = OFF;
		}
	}

	private void luz(ArrayList<String> parametros) {
		conector.Conectar(parametros);
		datos = conector.getDatos();
		try {
			S_foco1 = conector.getDato("estado", 0);
		} catch (JSONException e) {
			e.printStackTrace();
		}
		if (S_foco1 == ON) {
			TogFoco1.setChecked(true);
			int_foco1 = ON;
		}
		if (S_foco1 == OFF) {
			TogFoco1.setChecked(false);
			int_foco1 = OFF;
		}
	}

	private void pres(ArrayList<String> parametros) {
		conector.Conectar(parametros);
		datos = conector.getDatos();
		try {
			S_pres1 = conector.getDato("estado", 0);
		} catch (JSONException e) {
			e.printStackTrace();
		}
		if (S_pres1 == 1)
			LabPres.setText("SI");
		else
			LabPres.setText("NO");
	}

	private void temp(ArrayList<String> parametros) {
		conector.Conectar(parametros);
		datos = conector.getDatos();
		try {
			S_temp = conector.getDato("estado", 0);
		} catch (JSONException e) {
			e.printStackTrace();
		}
		LabTemp.setText(S_temp + " ºC");
	}

	private Runnable espera = new Runnable() {
		private int j;

		public void run() {
			if (j <= 1) {
				// label.setText(" " + j);
				j++;
				mHandler.postDelayed(this, 100);
			} else {
				mHandler.post(cambio);
				// label.append("termino, ");
				j = 0;
			}
		}
	};

	private Runnable cambio = new Runnable() {
		public void run() {
			luz(AL_luz);
			temp(AL_temp);
			pres(AL_pres);
			aire(AL_aire);
			mHandler.post(espera);
		}
	};

	protected void onPause() {
		super.onPause();
		mHandler.removeCallbacks(espera);
		mHandler.removeCallbacks(cambio);
		//finish();
	};

	protected void onDestroy() {
		super.onDestroy();
		mHandler.removeCallbacks(espera);
		mHandler.removeCallbacks(cambio);
		//finish();
	}

	private int SELECT_IMAGE = 237487;
	private int TAKE_PICTURE = 829038;

	private void dialogPhoto() {
		try {
			final CharSequence[] items = { "Seleccionar de la galería",
					"Hacer una foto" };

			AlertDialog.Builder builder = new AlertDialog.Builder(this);
			builder.setTitle("Seleccionar una foto");
			builder.setItems(items, new DialogInterface.OnClickListener() {
				public void onClick(DialogInterface dialog, int item) {
					switch (item) {
					case 0:
						Intent intent = new Intent(
								Intent.ACTION_PICK,
								android.provider.MediaStore.Images.Media.INTERNAL_CONTENT_URI);
						intent.setType("image/*");

						startActivityForResult(intent, SELECT_IMAGE);
						break;
					case 1:
						startActivityForResult(
								new Intent(
										android.provider.MediaStore.ACTION_IMAGE_CAPTURE),
								TAKE_PICTURE);
						break;
					}

				}
			});
			AlertDialog alert = builder.create();
			alert.show();
		} catch (Exception e) {
		}
	}

	public void onActivityResult(int requestCode, int resultCode, Intent data) {
		super.onActivityResult(requestCode, resultCode, data);
		try {
			if (requestCode == SELECT_IMAGE)
				if (resultCode == Activity.RESULT_OK) {
					Uri selectedImage = data.getData();
					imgPhoto.setImageBitmap(Scale_Image.loadBitmap(
							getPath(selectedImage), 500, 500));
					Log.e("select imagen", getPath(selectedImage));
					guardar(getPath(selectedImage));
				}
			if (requestCode == TAKE_PICTURE)
				if (resultCode == Activity.RESULT_OK) {
					Uri selectedImage = data.getData();
					imgPhoto.setImageBitmap(Scale_Image.loadBitmap(
							getPath(selectedImage), 500, 500));
					Log.e("take imagen", getPath(selectedImage));
					guardar(getPath(selectedImage));
				}
		} catch (Exception e) {

		}
	}

	public static void guardar(String imagen) {

		final int buffer_size = 1024;
		File sd = Environment.getExternalStorageDirectory();
		File ruta = new File(sd,RUTA);
		ruta.mkdir();
		File destino = new File(sd, RUTA + FILE);
		File origen = new File(imagen);
		Log.e("origen", origen.getAbsolutePath());
		Log.e("destino", destino.getAbsolutePath());
		try {
			if (sd.canWrite()) {
				destino.createNewFile();
				InputStream is = new FileInputStream(origen);
				OutputStream os = new FileOutputStream(destino);
				byte[] bytes = new byte[buffer_size];
				while (true) {
					int count = is.read(bytes, 0, buffer_size);
					if (count == -1)
						break;
					os.write(bytes, 0, count);
				}
			}

		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	private String getPath(Uri uri) {
		String[] projection = { android.provider.MediaStore.Images.Media.DATA };
		Cursor cursor = managedQuery(uri, projection, null, null, null);
		int column_index = cursor
				.getColumnIndexOrThrow(android.provider.MediaStore.Images.Media.DATA);
		cursor.moveToFirst();
		return cursor.getString(column_index);
	}

	public boolean onCreateOptionsMenu(Menu menu) {
		menu.add(Menu.NONE, 1, Menu.NONE, "Cambiar imagen");
		return true;
	}

	public boolean onOptionsItemSelected(MenuItem item) {
		switch (item.getItemId()) {

		case 1: {
			dialogPhoto();
			return true;
		}
		case 2: {
			return true;
		}
		case 3: {
			return true;
		}
		default:
			return super.onOptionsItemSelected(item);
		}
	}

	@Override
	public void onBackPressed() {
		if (bmp != null) {
			bmp.recycle();
			bmp = null;
			System.gc();
		}
		Intent intent = new Intent(SalaPB.this, Principal.class);
		startActivity(intent);
		finish();

		super.onBackPressed();
	}
	private class ExampleAction extends AbstractAction {

	    public ExampleAction() {
	        super(R.drawable.ic_title_home_default);
	    }

	    @Override
	    public void performAction(View view) {
	        Intent intent = new Intent(SalaPB.this, Principal.class);
			startActivity(intent);
			finish();
	    }
}}
