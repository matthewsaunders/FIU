package account.models;

import java.sql.DriverManager;
import java.sql.ResultSet;

import account.modelstest.SendEmail;

import com.mysql.jdbc.Connection;
import com.mysql.jdbc.PreparedStatement;
import com.mysql.jdbc.Statement;

public class PasswordReset {

	public boolean checkEmail(String username) {

		// To connect to the database
		String connectionURL = "jdbc:mysql://localhost:3306/test";
		Connection connection = null;
		Statement statement = null;
		ResultSet rs = null;
		String dbUsername = "root"; // Database username
		String dbPassword = "root1234!"; // Database password
	
		try {
			Class.forName("com.mysql.jdbc.Driver");
		} catch (Exception e) {
			System.out.println(" Unable to load driver. ");
		}
		try {
			connection = (Connection) DriverManager.getConnection(
					connectionURL, dbUsername, dbPassword);
			System.out.println(" Connection Established. ");

			// After this, create your own logic
			PreparedStatement st = (PreparedStatement) connection
					.prepareStatement("SELECT username, fname, password FROM Users WHERE username = ?");
			st.setString(1, username);
			rs = st.executeQuery();

			if (rs != null) {
				String email = "";
				String name = "";
				String pass = "";

				while (rs.next()) {
					email = rs.getString("username");
					name = rs.getString("fname");
					pass = rs.getString("password");
				}

				connection.close();
				if (username.compareTo(email) == 0) {

					//send(username, name, pass);
					SendEmail.send(username, name, "Forgot Password",  "You have requested your password for your Family Tree Account. " +
							"The password for your account is " + pass);

					return true;
				}
			}
		} catch (Exception e) {
			System.out.println(" Error connecting to database:  " + e);
		}
		return false;

		// username: accountsystem passoword: accounts
	}
	
}
