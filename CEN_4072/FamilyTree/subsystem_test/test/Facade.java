package test;

import java.sql.ResultSet;
import java.util.ArrayList;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

import account.models.sstest.Administration;
import account.models.sstest.Comments;
import account.models.sstest.LogInAndOut;
import account.models.sstest.Registration;
import account.models.sstest.User;
import account.models.sstest.getCommentsInfo;
import account.models.sstest.getUserRow;

public class Facade {
	private static Connection cStub;
	private static PreparedStatement psStub;
	private static ResultSet rsStub;
	private static DriverManagerStub dmStub = new DriverManagerStub();
	private static StatementStub sStub = new StatementStub();

	public void SetConnectionStub(Connection cStub) {
		this.cStub = cStub;
	}

	public void SetPreparedStatementStub(PreparedStatement psStub) {
		this.psStub = psStub;
	}

	public void SetResultSetStub(ResultSet rsStub) {
		this.rsStub = rsStub;
	}

	public void SetStatementStub(StatementStub sStub) {
		this.sStub = sStub;
	}

	// Start of Registration class in account.models
	public boolean doRegistration(String fName, String lName, String email,
			String pass) {
		Registration reg = new Registration(cStub);
		return reg.doRegistration(fName, lName, email, pass);
	}

	// End of Registration class in account.models

	// Start of LogInAndOut class in account.models
	public static boolean doLogin(String username, String password) {
		return LogInAndOut.doLogin(username, password);
	}

	// End of LogInAndOut class in account.models

	// Start of getUserRow class in account.models
	public static String[] getUserInfo(String username) {
		return getUserRow.getUserInfo(username);
	}

	// End of getUserRow class in account.models

	// Start of Administration class in account.models
	public static ArrayList<User> findNoAdmin() {
		Administration admin = new Administration(cStub, sStub, rsStub);
		return Administration.findNoAdmin();
	}

	public static boolean makeAdmin(ArrayList<User> newAdmins) {
		Administration admin = new Administration(cStub, sStub, rsStub);
		return Administration.makeAdmin(newAdmins);
	}

	public static void dropFromTable(ArrayList<User> list) {
		Administration.dropFromTable(list);
	}

	public static ArrayList<User> showAdminRequest() {
		return Administration.showAdminRequest();
	}

	public static String sendRequest(String username, String fname, String lname) {
		return Administration.sendRequest(username, fname, lname);
	}

	// End of Administration class in account.models

	// Start of getComments class in account.models
	public static ArrayList<Comments> getComments() {
		return getCommentsInfo.getComments();
	}
	// End of getComments class in account.models

	// Start of Link class in account.models
	/*
	 * public static int getMemberID(String fName, String lName, String bday) {
	 * return Link.getMemberID(fName, lName, bday); }
	 */
	// End of Link class in account.models

	/*
	 * //Start of MakeReplay in account.models public static void postReplay(int
	 * id, String text, String owner) { MakeReplay.postReplay(id, text, owner);
	 * }
	 * 
	 * public static int postComment(String text, String owner) { return
	 * MakeReplay.postComment(text, owner); }
	 * 
	 * public static String getLast(int total) { return
	 * MakeReplay.getLast(total); }
	 */
}
