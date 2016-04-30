package administration.Controllertest;

import java.util.ArrayList;

public class ResultSet {
	
	private boolean stub = true ;
	
	
	public boolean next(){
		
	    return stub ; 
		
	}
	
	
	public String getString(String element){
		
		this.stub = false ;
		
	    return element ;
		
	}
	
	public void setNext(boolean a){
		
		stub = a ;
		
	}

}
