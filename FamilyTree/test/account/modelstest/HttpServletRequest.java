package account.modelstest;

import java.util.Map;

public abstract class HttpServletRequest {
	
	public abstract Map getParameterMap();
	
	public abstract String getParameter(String key);
	
	public abstract boolean containsKey(String key);
	
	public abstract void setState(String fname, String lname, String email, String pass);
	
}
