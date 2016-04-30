package account.modelstest;

import java.sql.DriverManager;
import java.sql.ResultSet;

import com.mysql.jdbc.Connection;
import com.mysql.jdbc.PreparedStatement;
import com.mysql.jdbc.Statement;

public class getUserRow {
	
	private String username;
	private String fname;
	private String lname;
	private String permission;
	
	public getUserRow(String username, String fname, String lname, String permission){
		this.username = username;
		this.fname = fname;
		this.lname = lname;
		this.permission = permission;
	}
	
	public String[] getUserInfo(String username) {
		String [] row = {username, fname, lname, permission};		
		return row;
	}

}
