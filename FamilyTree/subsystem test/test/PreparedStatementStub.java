package test;

import java.sql.ResultSet;
import java.sql.SQLException;

import com.mysql.jdbc.MySQLConnection;
import com.mysql.jdbc.PreparedStatement;


public class PreparedStatementStub extends PreparedStatement
{
	private ResultSetStub rs;
	//private static final MySQLConnection mysql;
	
	string connStr = "server=localhost;user=root;database=world;port=3306;password=******;";
	MySQLConnection conn = new MySQLConnection(connStr);
	
	public PreparedStatementStub() throws SQLException
	{
		super(mysql, "");
		// TODO Auto-generated constructor stub
	}
	
	public PreparedStatementStub(MySQLConnection conn, String catalog)
			throws SQLException {
		super(conn, catalog);
		// TODO Auto-generated constructor stub
	}
	
	public ResultSet executeQuery()
	{
		return rs;
	}

	public void SetResultSet(ResultSetStub rs) 
	{
		this.rs = rs;		
	}

}
