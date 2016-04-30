package account.modelstest;

import java.sql.DriverManager;
import java.sql.ResultSet;

import com.mysql.jdbc.*;

import com.mysql.jdbc.Connection;
import com.mysql.jdbc.PreparedStatement;
import com.mysql.jdbc.Statement;

public class LogInAndOut {
	
	private boolean status;
	
	public LogInAndOut(boolean flag){
		status = flag;
	}
	
	public boolean doLogin(String username, String password) {
		return status;
	}

}
