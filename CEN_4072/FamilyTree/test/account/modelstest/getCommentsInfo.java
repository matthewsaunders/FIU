package account.modelstest;

import java.sql.DriverManager;
import java.sql.ResultSet;
import java.util.ArrayList;

import account.modelstest.Comments;

import com.mysql.jdbc.Connection;
import com.mysql.jdbc.PreparedStatement;
import com.mysql.jdbc.Statement;

public class getCommentsInfo {
	
	ArrayList<Comments> list; 
	
	public getCommentsInfo(){
		list = new ArrayList<Comments>();
	}
	
	public void addComment(int id, int parent, String date, String owner, String text, String fname, String lname){
		list.add(new Comments(id, parent, date, owner, text, fname, lname));
	}
	
	public ArrayList<Comments> getComments() {
		/*
		Comments newcomment = new Comments(3,0,"06/06/2006","hulk","Hulk Smash!!!","Bruce","Banner");
		newcomment = new Comments(17,3,"06/07/2006","xxdarkKnightxx","There's only room in this town for one Bruce...","Bruce","Wayne");
		*/
		return list;
	}
}


