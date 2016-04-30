package account.modelstest;

import java.sql.DriverManager;
import java.sql.ResultSet;

import account.modelstest.SendEmail;

import com.mysql.jdbc.Connection;
import com.mysql.jdbc.PreparedStatement;
import com.mysql.jdbc.Statement;

public class PasswordReset {

	private boolean flag;
	
	public PasswordReset(boolean b){
		flag = b;
	}
	
	public void setFlag(boolean b){
		flag = b;
	}
	
	public boolean checkEmail(String username) {
		return flag;
	}
	
}
