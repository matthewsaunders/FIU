package account.models.test;

import java.sql.DriverManager;
//import java.sql.ResultSet;




import javax.servlet.http.HttpSession;

import test.ConnectionStub;
import test.PreparedStatementStub;
import test.ResultSetStub;

//import com.mysql.jdbc.Connection;
//import com.mysql.jdbc.PreparedStatement;

public class MakeReplay {

	public static void postReplay(int id, String text, String owner) {

		// To connect to the database
		String connectionURL = "jdbc:mysql://localhost:3306/test";
		ConnectionStub connection = null;
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

			// After this, create your own logic
			PreparedStatementStub st = (PreparedStatementStub) connection
					.prepareStatement("CALL insert_replay(?,?,?)");
			st.setString(1, text);
			st.setInt(2, id);
			st.setString(3, owner);
			st.executeQuery();
			
			connection.close();
		} catch (Exception e) {
			System.out.println(" Error connecting to database:  " + e);
		}
	}
	
	public static int postComment(String text, String owner) 
	{
		
		int id = -1;
		// To connect to the database
		String connectionURL = "jdbc:mysql://localhost:3306/test";
		ConnectionStub connection = null;
		ResultSetStub rs = null;
		String dbUsername = "root";//"ft_accounts"; // Database username
		String dbPassword = "1234";//"2K7hWXvfay9cB2qW"; // Database password

		try 
		{
			Class.forName("com.mysql.jdbc.Driver");
		} 
		catch (Exception e) 
		{
			System.out.println(" Unable to load driver. ");
		}
		try 
		{
			connection = (ConnectionStub) DriverManager.getConnection(
					connectionURL, dbUsername, dbPassword);
			//System.out.println(" Connection Established. ");

			// After this, create your own logic
			PreparedStatementStub st = (PreparedStatementStub) connection
					.prepareStatement("CALL insert_comment(?,?)");
			st.setString(1, text);
			st.setString(2, owner);
			rs = (ResultSetStub) st.executeQuery();
			
			if (rs != null) 
				while (rs.next()) 
					id = rs.getInt("comment_id");
			connection.close();
		} catch (Exception e) {
			System.out.println(" Error connecting to database:  " + e);
		}
	return id;
	}
	
	public static String getLast(int total) {
		
		int result = 0;
		String json = "";
		// To connect to the database
		String connectionURL = "jdbc:mysql://localhost:3306/test";
		ConnectionStub connection = null;
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

			// After this, create your own logic
			PreparedStatementStub st = (PreparedStatementStub) connection.prepareStatement("SELECT Count(*) as total FROM Comments");		
			rs = (ResultSetStub) st.executeQuery();
			if (rs != null){
				while (rs.next()){
					result = rs.getInt("total");
				}
			}
			
			if(result > total){
				result = result - total;
				st = (PreparedStatementStub) connection.prepareStatement("SELECT comment_id,comment_family,content,fname,lname FROM Comments,Users where created_by = username Order by comment_id Desc Limit ?");
				st.setInt(1, result);
				rs = (ResultSetStub) st.executeQuery();
				if (rs != null){ 
					json = "[";
					while (rs.next()){
						json = json + "{\"id\":\"" + rs.getInt("comment_id");
						json = json + "\",\"parent\":\"" + rs.getInt("comment_family");
						json = json + "\",\"text\":\"" + rs.getString("content");
						json = json + "\",\"first\":\"" + rs.getString("fname");
						json = json + "\",\"last\":\"" + rs.getString("lname");
						json = json + "\",\"total\":\"" + result--;
						json = json + "\"},";
					}
					json = json.substring(0,json.length()-1);
					json = json + "]";
				}
			}			
		} catch (Exception e) {
			System.out.println("Error connecting to database: " + e);
		}
		return json;
	}
}
