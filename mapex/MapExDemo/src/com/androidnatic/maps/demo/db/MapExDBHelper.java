package com.androidnatic.maps.demo.db;

import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

import android.content.ContentValues;
import android.content.Context;
import android.content.res.Resources;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.os.Environment;

import com.androidnatic.maps.demo.R;
import com.androidnatic.maps.model.HeatPoint;


public class MapExDBHelper extends SQLiteOpenHelper {
	
	private final Context mHelperContext;
    private SQLiteDatabase mDatabase;
	private final static String DB_NAME = "HEAT_DB";
	
	public MapExDBHelper(Context context){
		
		super(context,Environment.getExternalStorageDirectory().getAbsolutePath() + "/Android/data/com.androidnatic.maps/files/"+DB_NAME,null,1);
		this.mHelperContext = context;
	}
	
	@Override
	public void onCreate(SQLiteDatabase db) {
		String table_heat = "CREATE TABLE IF NOT EXISTS HEAT_SAMPLE(ID INTEGER PRIMARY KEY, LATITUDE REAL, LONGITUDE REAL)";
		mDatabase = db;
		mDatabase.execSQL(table_heat);
		loadDB(db);
	}

	@Override
	public void onUpgrade(SQLiteDatabase arg0, int arg1, int arg2) {
		// TODO Auto-generated method stub

	}

	private void loadDB(SQLiteDatabase db){
		
		Resources r = mHelperContext.getResources();
		InputStream is = r.openRawResource(R.raw.wiki_br);
		Scanner scanner = new Scanner(is);
		scanner.useDelimiter("\n");
		ContentValues values = new ContentValues();
		values.put("LATITUDE", 0);
		values.put("LONGITUDE", 0);
		try{
		db.beginTransaction();
		while(scanner.hasNext()){
			String line = scanner.next();
			String[] entry = line.split(" ");
			values.put("LATITUDE", Float.valueOf(entry[0]));
			values.put("LONGITUDE", Float.valueOf(entry[1]));
			db.insert("HEAT_SAMPLE", null, values);
		}
		}catch (Exception e) {
			
		}finally{
			db.setTransactionSuccessful();
			db.endTransaction();
		}
	}
	
	public List<HeatPoint> loadPoints(int[][] bounds){
		String sql = "SELECT LATITUDE,LONGITUDE FROM HEAT_SAMPLE WHERE LATITUDE >= " + bounds[0][0]/1E6 + " AND LATITUDE <= " + bounds[1][0]/1E6 + " AND LONGITUDE >= " + bounds[0][1]/1E6 + " AND LONGITUDE <= " + bounds[1][1]/1E6;
		SQLiteDatabase db = getReadableDatabase();
		Cursor cursor = null;
		cursor = db.rawQuery(sql, null);
		List<HeatPoint> points = new ArrayList<HeatPoint>(cursor.getCount());
		if(cursor.moveToFirst()){
			do {
				HeatPoint point = new HeatPoint();
				point.lon = (cursor.getFloat(cursor.getColumnIndex("LONGITUDE")));
				point.lat = (cursor.getFloat(cursor.getColumnIndex("LATITUDE")));
				
				points.add(point);
			} while (cursor.moveToNext());
		}
		return points;
	}
	
	
	
}
