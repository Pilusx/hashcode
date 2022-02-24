import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.Scanner;

public class Solution {
	public static void main(String[] args) throws FileNotFoundException, UnsupportedEncodingException {
		
		/*-------READING from a file-------*/
		
		/* 1.)
		 * saves the input, if WE KNOW THE SIZE of the input
		 */
		
		Scanner scan = new Scanner(new File("./input.txt"));
		
		int n = 0; // the length of our array
		String[] ar = new String[3];
		
		int i=0;
		while(scan.hasNext()) {
			ar[i]=scan.next();
		}
		
		
		/* 2.)
		 * if we DO NOT KNOW THE SIZE of the input
		 */
		
		scan = new Scanner(new File("./input.txt"));
		
		ArrayList<String> list = new ArrayList<String>();
		//i=0;
		while(scan.hasNext()) {
			list.add(scan.next());
			//System.out.println(list.get(i));
			//i++;
			
		}
		scan.close();
		
		/* for printing the elements of the list
		for(int j=0; i<list.size(); j++) {
			System.out.println(list.get(j));
		}
		*/
		
		/* -------WRITING to a file-------*/
		
		PrintWriter pw = new PrintWriter("output.txt", "UTF-8");
		pw.println("HashCode");
		
		pw.close();
		
	}

}
