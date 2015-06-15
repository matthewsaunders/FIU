package test;

import com.mysql.jdbc.PreparedStatement;
import java.sql.ResultSet;
import java.util.ArrayList;

import com.mysql.jdbc.Connection;

import account.models.test.Comments;
import account.models.test.LogInAndOut;
import account.models.test.MakeReplay;
import account.models.test.User;
import account.models.test.Registration;
import account.models.test.Administration;
import account.models.test.getCommentsInfo;
import account.models.test.Link;

public class Facade 
{
	private Connection cStub;
	private PreparedStatement psStub;
	private ResultSet rsStub;
	
	public void SetConnectionStub(Connection cStub)
	{
		this.cStub = cStub;
	}
	
	public void SetPreparedStatementStub(PreparedStatement psStub)
	{
		this.psStub = psStub;
	}
	
	public void SetResultSetStub(ResultSet rsStub)
	{
		this.rsStub = rsStub;
	}
	
	//Start of Registration class in account.models
	public boolean doRegistration(String fName, String lName, String email,
			String pass) 
	{
		Registration reg = new Registration(cStub, psStub, rsStub);
		return reg.doRegistration(fName, lName, email, pass);
	}
	//End of Registration class in account.models
	
	//Start of LogInAndOut class in account.models
	public static boolean doLogin(String username, String password) 
	{
		return LogInAndOut.doLogin(username, password);
	}
	//End of LogInAndOut class in account.models
	
	//Start of User class in account.models
	/*public void setUserName(String userName) 
	{
		User newUser = new User(null,null,null,null);
		newUser.setUserName(userName);
	}*/
	//End of User class in account.models
	
	//Start of Administration class in account.models
	public static boolean makeAdmin(ArrayList<User> newAdmins) 
	{
		return Administration.makeAdmin(newAdmins);	
	}
	
	public static void dropFromTable(ArrayList<User> list) 
	{
		Administration.dropFromTable(list);
	}
	
	public static ArrayList<User> showAdminRequest() 
	{
		return Administration.showAdminRequest();
	}
	
	public static ArrayList<User> findNoAdmin() 
	{
		return Administration.findNoAdmin();
	}
	
	public static String sendRequest(String username, String fname, String lname) 
	{
		return Administration.sendRequest(username, fname, lname);
	}
	//End of Administration class in account.models
	
	/*//Start of getComments class in account.models
	public static ArrayList<Comments> getComments() 
	{
		return getCommentsInfo.getComments();
	}
	//End of getComments class in account.models
*/	
	//Start of Link class in account.models
	/*public static int getMemberID(String fName, String lName, String bday)
	{
		return Link.getMemberID(fName, lName, bday);
	}*/
	//End of Link class in account.models
	
	/*//Start of MakeReplay in account.models
	public static void postReplay(int id, String text, String owner) 
	{
		MakeReplay.postReplay(id, text, owner);
	}
	
	public static int postComment(String text, String owner) 
	{
		return MakeReplay.postComment(text, owner);
	}
	
	public static String getLast(int total) 
	{
		return MakeReplay.getLast(total);
	}*/
}
