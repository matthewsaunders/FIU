package account.modelstest;

import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

//import org.apache.catalina.ant.FindLeaksTask;


import account.modelstest.StubAdministration;
import account.modelstest.User;

import com.mysql.jdbc.Connection;
import com.mysql.jdbc.PreparedStatement;
import com.mysql.jdbc.Statement;

public class StubAdministration {

	private ArrayList<User> list;
	private ArrayList<User> nonAdmin;
	private boolean makeAdmin;
	private int messageIndex;
	private static String[] messages = {"Your request has been sent!", "An error occurred while processing your request", "Your request is already waiting for approval"};
	
	
	public StubAdministration(boolean makeAdmin){
		list = new ArrayList<User>();
		nonAdmin = new ArrayList<User>();
		this.makeAdmin = makeAdmin;
		messageIndex = 0;
	}
	
	public void addNonAdmin(User u){
		list.add(u);
	}
	
	public ArrayList<User> findNoAdmin() {
		return nonAdmin;
	}

	/**
	 * Gets a list with the new users to be converted into admins
	 * 
	 * @param newAdmins
	 * @return
	 */
	public boolean makeAdmin(ArrayList<User> newAdmins) {
		return makeAdmin;
	}

	public void setMessageIndex(int index){
		messageIndex = index;
	}
	
	public String sendRequest(String username, String fname, String lname) {
		return messages[messageIndex];
	}
	
	public String getRequest(){
		return messages[messageIndex];
	}

	public void addAdmin(User u){
		list.add(u);
	}
	
	public ArrayList<User> showAdminRequest() {
		ArrayList<User> list = new ArrayList<User>();
		return list;
	}

	public void dropFromTable(ArrayList<account.modelstest.User> denied) {

	}
}