package administration.Controllertest;

import java.sql.SQLException;

/*
 * Stub class for SQL derived class Connection. 
 * It passes dummy values for instances of PreparedStament objects.
 */
public class Connection {
	
	//Prepared Statement variable to manipulate.
	private PreparedStatement stub = new PreparedStatement() ;
	
	/*
	 * Returns the PreparedStatement previously declared ignoring
	 * query contents.
	 */
	public PreparedStatement prepareStatement(String query){
		
		return this.stub;
		
	}
	
	/*
	 * Indicates termination of a fake connection by outputting a message.
	 */
	public void close() throws SQLException{
		
		System.out.print("Closing Connection.") ;
	}
	
	/*
	 * Sets the value of a PreparedStatement in case it is necessary to 
	 * pass dummy values.
	 */
	public void setPreparedStatement (PreparedStatement a){
		
		this.stub = a ;
	}

}
