package account.models.test;

import java.sql.DriverManager;
//import java.sql.ResultSet;


import test.ConnectionStub;
import test.PreparedStatementStub;
import test.ResultSetStub;

/*import com.mysql.jdbc.Connection;
import com.mysql.jdbc.PreparedStatement;
import com.mysql.jdbc.Statement;*/

public class getUserRow {
	
	public static String[] getUserInfo(String username) {
		
		String [] row = new String[4];

		//To connect to the database
		String connectionURL = "jdbc:mysql://localhost:3306/test";
		ConnectionStub connection = null;
		//Statement statement = null;
		ResultSetStub rs = null;
		String dbUsername = "root"; // Database username
		String dbPassword = "1234"; // Database password

		try {
			Class.forName("com.mysql.jdbc.Driver");
		} catch (Exception e) {
			System.out.println(" Unable to load driver. ");
		}
		try {
			connection = (ConnectionStub) DriverManager.getConnection(
					connectionURL, dbUsername, dbPassword);
			//System.out.println(" Connection Established. ");
			
			//After this, create your own logic
			PreparedStatementStub st = (PreparedStatementStub) connection.prepareStatement("SELECT * FROM Users WHERE username = ?");
			st.setString(1, username);
			rs = (ResultSetStub) st.executeQuery();

			if (rs != null) {			
				
				while (rs.next()) {
					 row[0] = rs.getString("username");
					 row[1] = rs.getString("fname");
					 row[2] = rs.getString("lname");
					 row[3] = rs.getString("privileges");
				}
			}
			connection.close();
		} catch (Exception e) {
			System.out.println(" Error connecting to database:  " + e);
		}
		
		return row;

		// username: accountsystem passoword: accounts
	}

}
