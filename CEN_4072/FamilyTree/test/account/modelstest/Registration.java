package account.modelstest;

import java.sql.DriverManager;
import java.sql.ResultSet;
import java.util.regex.Pattern;

import com.mysql.jdbc.Connection;
import com.mysql.jdbc.PreparedStatement;
import com.mysql.jdbc.Statement;

public class Registration {

	private boolean registration;
	
	public Registration(boolean reg){
		registration = reg;
	}
	
	public void setTrue(){
		registration = true;
	}
	
	public void setFalse(){
		registration = false;
	}
	
	public boolean doRegistration(String fName, String lName, String email,
			String pass) {
		//registration successful
		return registration;
	}
}
