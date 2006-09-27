package openjaus.nodemanager;

/** A threadsafe counter.  Used to generate unique names for each thread. */
public class Counter {
	private int count = 0;
	private String name = "";
	
	public Counter(String name){
		this.name = name;
	}
	public synchronized int next(){
		return ++count;
	}
	public synchronized String nextName(){
		return name + "-" + next();
	}
}
