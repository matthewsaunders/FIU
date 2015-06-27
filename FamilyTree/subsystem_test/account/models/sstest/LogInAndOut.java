package account.models.sstest;

import java.sql.DriverManager;
//import java.sql.ResultSet;

import test.ConnectionStub;
import test.DriverManagerStub;
import test.PreparedStatementStub;
import test.ResultSetStub;

import com.mysql.jdbc.*;

/*import com.mysql.jdbc.Connection;
 import com.mysql.jdbc.PreparedStatement;
 import com.mysql.jdbc.Statement;*/

public class LogInAndOut {
	private static ConnectionStub connection;

	public static boolean doLogin(String username, String password) {
		// To connect to the database
		String connectionURL = "jdbc:mysql://localhost:3306/test";

		ResultSetStub rs = null;
		String dbUsername = "root"; // Database username
		String dbPassword = "1234"; // Database password

		try {
			Class.forName("com.mysql.jdbc.Driver");
		} catch (Exception e) {
			System.out.println(" Unable to load driver. ");
		}
		try {
			connection = (ConnectionStub) DriverManagerStub.getConnection(
					connectionURL, dbUsername, dbPassword);
			// System.out.println(" Connection Established. ");

			// After this, create your own logic
			PreparedStatementStub st = (PreparedStatementStub) connection
					.prepareStatement("SELECT username, password FROM Users WHERE username = ?");
			st.setString(1, username);
			rs = (ResultSetStub) st.executeQuery();

			if (rs != null) {
				String user = "";
				String pass = "";

				while (rs.next()) {
					user = rs.getString("username");
					pass = rs.getString("password");
				}

				connection.close();
				if (username.compareTo(user) == 0
						&& password.compareTo(pass) == 0)
					return true;
			}
		} catch (Exception e) {
			System.out.println(" Error connecting to database:  " + e);
		}
		return false;
	}
}
