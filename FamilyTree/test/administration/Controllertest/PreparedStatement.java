package administration.Controllertest;

public class PreparedStatement extends Statement {
	
	private ResultSet queryResult ;
	
	public void setQueryResult(ResultSet result){
		queryResult = result;
	}
	
	public int executeUpdate(){
		
		return 0 ;
		
	}
	
	public ResultSet executeQuery(){
		return queryResult;
	}
	
	public void setString(int number, String character){
		
		
	}

}
