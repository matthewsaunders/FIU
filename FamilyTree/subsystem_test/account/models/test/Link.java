package account.models.test;

import java.sql.Date;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;

import test.ConnectionStub;
import test.StatementStub;
import test.ResultSetStub;

public class Link {

	public static int getMemberID(String fName, String lName, String bday) {

		// To connect to the database
		String connectionURL = "jdbc:mysql://localhost:3306/test";
		ConnectionStub connection = null;
		StatementStub statement = null;
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
			System.out.println(" Connection Established. ");

			StatementStub st = (StatementStub) connection
					.prepareStatement("SELECT member_id FROM Members WHERE first_name = ? AND last_name = ? AND birthdate = ?");
			st.setString(1, fName);
			st.setString(2, lName);
			st.setString(3, bday);

			rs = (ResultSetStub) st.executeQuery();

			if (!rs.next()) {
				return -1;
			}
			return rs.getInt(1);

		} catch (Exception e) {
			System.out.println(" Error connecting to database:  " + e);
		}
		try {
			connection.close();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return 0;

	}
}
