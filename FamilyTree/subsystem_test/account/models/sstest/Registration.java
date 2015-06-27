package account.models.sstest;

//import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Connection;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.PreparedStatement;

import test.DriverManagerStub;

public class Registration {
	private Connection connection;
	private PreparedStatement st;
	private ResultSet rs;

	public Registration(Connection cStub) {
		connection = cStub;
		// TODO Auto-generated constructor stub
	}

	public boolean doRegistration(String fName, String lName, String email,
			String pass) {

		// To connect to the database
		String connectionURL = "jdbc:mysql://localhost:3306/test";

		String dbUsername = "root"; // Database username
		String dbPassword = "1234"; // Database password

		try {
			Class.forName("com.mysql.jdbc.Driver");
		} catch (Exception e) {
			System.out.println(" Unable to load driver. ");
		}
		try {
			connection = DriverManagerStub.getConnection(connectionURL,
					dbUsername, dbPassword);
			System.out.println(" Connection Established. ");

			// After this, create your own logic

			st = connection
					.prepareStatement("SELECT * FROM Users WHERE username = ?");
			st.setString(1, email);
			rs = (ResultSet) st.executeQuery();

			// return false if email already taken
			if (rs == null) {
				connection.close();
				System.out.println(" Reached null. ");
				return false;
			} else {
				String query = "INSERT INTO Users (" + " username," + " fname,"
						+ " lname," + " password," + " privileges ) VALUES ("
						+ "?, ?, ?, ?, ?)";

				st = (PreparedStatement) connection.prepareStatement(query);
				st.setString(1, email);
				st.setString(2, fName);
				st.setString(3, lName);
				st.setString(4, pass);
				st.setString(5, "u");

				st.executeUpdate();
				connection.close();
			}
		}
		// return false if there was any problem with the connection
		catch (Exception e) {
			System.out.println(" Error inserting into the database: " + e);
			return false;
		}

		// registration successful
		return true;

	}

}
