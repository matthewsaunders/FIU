package account.modelstest;

import java.sql.DriverManager;
import java.sql.ResultSet;
import java.util.regex.Pattern;

import account.modelstest.*;

import com.mysql.jdbc.Connection;
import com.mysql.jdbc.PreparedStatement;
import com.mysql.jdbc.Statement;

public class StubRegistration extends Registration {

	public boolean doRegistration(String fName, String lName, String email,
			String pass) {
		//registration successful
		return true;
		
	}

}
