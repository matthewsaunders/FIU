package account.models;

import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

//import org.apache.catalina.ant.FindLeaksTask;


import account.models.Administration;
import account.models.User;

import com.mysql.jdbc.Connection;
import com.mysql.jdbc.PreparedStatement;
import com.mysql.jdbc.Statement;

public class Administration {

	static String connectionURL = "jdbc:mysql://localhost:3306/test";
	static Connection connection = null;
	static Statement statement = null;
	static ResultSet rs = null;
	static String dbUsername = "root"; // Database username
	static String dbPassword = "root1234!"; // Database password
	
	public static ArrayList<User> findNoAdmin() {

		ArrayList<User> nonAdmin = new ArrayList<User>();

		// String connectionURL =
		// "jdbc:mysql://softeng.cs.fiu.edu:3306/family_tree__accounts_only";
		// Connection connection = null;
		// //Statement statement = null;
		// ResultSet rs = null;
		// String dbUsername = "ft_accounts"; // Database username
		// String dbPassword = "2K7hWXvfay9cB2qW"; // Database password

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
					.prepareStatement("SELECT username, fname, lname, privileges FROM Users WHERE privileges = ?");
			st.setString(1, "u");
			rs = st.executeQuery();

			if (rs != null) {
				String user = "";
				String fname = "";
				String lname = "";
				String privileges = "";

				while (rs.next()) {
					user = rs.getString("username");
					fname = rs.getString("fname");
					lname = rs.getString("lname");
					privileges = rs.getString("privileges");

					User user1 = new User(user, fname, lname, privileges);

					nonAdmin.add(user1);
					// System.out.println(user);
				}
				connection.close();
			}
		} catch (Exception e) {
			System.out.println(" Error connecting to database:  " + e);
		}

		return nonAdmin;
	}

	/**
	 * Gets a list with the new users to be converted into admins
	 * 
	 * @param newAdmins
	 * @return
	 */
	public static boolean makeAdmin(ArrayList<User> newAdmins) {

		int totalUsersToChange = newAdmins.size(); // record number of users to
													// be changed

		if (totalUsersToChange == 0) {
			// Empty list of users passed
			System.err.println("No users in the list");
			return false;
		}

		try {
			connection = (Connection) DriverManager.getConnection(
					connectionURL, dbUsername, dbPassword);
			System.out.println(" Connection Established. ");
		} catch (Exception e) {
			e.printStackTrace();
			return false;
		}

		int noChange = 0; // Count the amount of users no changed
		for(int i = 0; i < newAdmins.size(); i++) {

			String username = newAdmins.get(i).getUserName(); // saves the
																	// username

			try {
				String query = "UPDATE Users SET privileges = 'a' WHERE username = '"
						+ username + "'";
				statement = (PreparedStatement) connection
						.prepareStatement(query);
				statement.executeUpdate(query);

			} catch (Exception e) {
				e.printStackTrace();
				noChange++;
			}

		}
		try {
			connection.close();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		if (totalUsersToChange == noChange) {
			System.err.println("No users were changed");
			return false;
		}

		return true;
	}

	public static String sendRequest(String username, String fname, String lname) {

		// Connect to database
		try {
			connection = (Connection) DriverManager.getConnection(
					connectionURL, dbUsername, dbPassword);
			System.out.println(" Connection Established. ");
		} catch (Exception e) {
			e.printStackTrace();
			return "Error Conecting to Database";
		}

		PreparedStatement st;
		try {
			st = (PreparedStatement) connection
					.prepareStatement("SELECT * FROM AdminRequest WHERE requested_by = ?");
			st.setString(1, username);
			rs = st.executeQuery();

			if (!rs.next()) {
				try {
					String query = "INSERT INTO AdminRequest (requested_by, fname, lname) VALUES (?, ?, ?)";

					st = (PreparedStatement) connection.prepareStatement(query);
					st.setString(1, username);
					st.setString(2, fname);
					st.setString(3, lname);

					st.executeUpdate();
					connection.close();
					
					return "Your request has been sent!";
				} catch (Exception e) {
					e.printStackTrace();
					return "An error occurred while processing your request";
				}
			} else {
				// if(rs.getString("requested_by").equals(username))
				return "Your request is already waiting for approval";
			}
		} catch (Exception e) {
			e.printStackTrace();
			return "Error Connecting to Database";
		}
	}

	public static ArrayList<User> showAdminRequest() {

		ArrayList<User> list = new ArrayList<User>();

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
					.prepareStatement("SELECT * FROM AdminRequest");
			rs = st.executeQuery();

			String username = "";
			String fname = "";
			String lname = "";
			while (rs.next()) {

				User u = new User(null, null, null, null);

				username = rs.getString("requested_by").toString();
				fname = rs.getString("fname").toString();
				lname = rs.getString("lname").toString();

				u.setUserName(username);
				u.setFname(fname);
				u.setLname(lname);

				list.add(u);
			}

			connection.close();
		} catch (Exception e) {
			System.out.println(" Error connecting to database:  " + e);
		}

		return list;
	}

	public static void dropFromTable(ArrayList<User> list) {

		try {
			connection = (Connection) DriverManager.getConnection(
					connectionURL, dbUsername, dbPassword);
			System.out.println(" Connection Established. ");
		} catch (Exception e) {
			e.printStackTrace();
		}

		while (!list.isEmpty()) {
			String username = list.remove(0).getUserName(); // saves the
															// username
			System.out.println("User: " + username);
			try {
				String query = "DELETE FROM AdminRequest WHERE requested_by = '"
						+ username + "'";
				statement = (PreparedStatement) connection
						.prepareStatement(query);
				statement.executeUpdate(query);

			} catch (Exception e) {
				e.printStackTrace();
			}
		}
		try {
			connection.close();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

	public static void main(String[] args) {
		//
		// //ArrayList<User> test = new ArrayList<User>();
		ArrayList<User> test = Administration.showAdminRequest();
		// //FindNonAdmin test2 = new FindNonAdmin();
		//
		// //test = test2.findNoAdmin();
		//
		dropFromTable(test);
		// while (!test.isEmpty()) { System.out.println(test.remove(0).fname); }
		//
	}

	// public static void main(String[] args) {
	//
	// ArrayList<User> test = Administration.findNoAdmin();
	// Administration.makeAdmin(test);
	// test = Administration.findNoAdmin();
	//
	// while (!test.isEmpty()) {
	// System.out.println(test.remove(0).userName);
	// }
	// }

}
