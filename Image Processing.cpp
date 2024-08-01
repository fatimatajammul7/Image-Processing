#include<iostream>
	#include<fstream>
	#include<string>
	#include<cstdlib>
	#include<cmath>

	using namespace std;
	bool Saved = false;

	#define MaxRows 500
	#define MaxCols 500

	struct grayImage{

	    grayImage(){

	        Rows = Cols = 0;
	        loaded = false;
	        for(int r = 0; r< MaxRows; r++)
	            for(int c = 0; c< MaxCols; c++)
	                Image[r][c] = 0;
	    }

	    unsigned short setPixel(unsigned short value, int r, int c) {

	        if (r >= Rows || c >= Cols || r < 0 || c < 0 || value < 0 || value > Maximum)
	            return -1;

	        Image[r][c] = value;
	        return value;
	    }

	    int getPixel(int r, int c){
	        /*
	        The Function for reading value of a single pixel
	        */

	        if (r >= Rows || c >= Cols || r < 0 || c < 0)
	            return -1;
	        return Image[r][c];
	    }

	    int setRows(int rows){
	        /*
	        The Function for changing the value of Rows of an Image
	        */


	        if (rows < 1 || rows > MaxRows)
	            return -1;
	        Rows = rows;
	        return Rows;
	    }
	    int getRows(){
	        /*
	        The Function for reading the value of Rows of an Image
	        */

	        return Rows;
	    }

	    int setCols(int cols){
	        /*
	        The Function for changing the value of Columns of an Image
	        */
	        if (cols < 1 || cols > MaxCols)
	            return -1;
	        Cols = cols;
	        return Cols;
	    }

	    int getCols() {
	        /*
	        The Function for reading the value of Rows of an Image
	        */
	        return Cols;
	    }

	    void combineSideBySide(grayImage& Debuggers, int fillValue = 0){
	    	
			 for(int r=0;r<Debuggers.Rows;r++) 
			 	for(int c=0;c<Debuggers.Cols;c++){
			 		
			 		if(Cols+c<MaxCols)
			 		
	        			 Image[r][Cols + c]= Debuggers.Image[r][c] ;
				 }
	        		Cols += Debuggers.Cols;
	        		
			if( Cols > MaxCols ||Rows <Debuggers.Rows  ) {
				Cols =  MaxCols;
				Rows =Debuggers.Rows;
			}	

			
	    }

	    void combineTopToBottom(grayImage& Debuggers, int fillValue = 0) {
	    	
		    for (int r= 0;r< Debuggers.Rows ;r++) 
		    	
		  		for( int c = 0; c< Debuggers.Cols;c++) {
	        		if (Rows+ r <MaxRows ) 
	        			
	        			
	        			  Image[Rows + r ][c] =Debuggers.Image[r][c];
					

				}
						 Rows += Debuggers.Rows;
						 
	        if (Rows >MaxRows ||Cols< Debuggers.Cols  ) {
	        	Rows = MaxRows;
	        	Cols = Debuggers.Cols;
			}


	    }

	    void FadeIn(grayImage& Debuggers, int Frames, int Seconds, string BaseFileName){
		grayImage XYZ;
			double SS =1.0 /( Frames*Seconds );
	    	int i,j;
	    	
	    	i=Rows;
			if (i< Debuggers.Rows )
				i=Debuggers.Rows;
			
			
			j=Cols;
			if( j< Debuggers.Cols  )
				j=Debuggers.Cols;
			
			
			
			XYZ.Rows=i; XYZ.Cols=j;
			XYZ.loaded = true;XYZ.Maximum= Maximum  ;
			
			if(  Maximum< Debuggers.Maximum)
				
				XYZ.Maximum=  Debuggers.Maximum;
				
			
			
			int count  =0;
			for(double b=1; b>=0; b-=SS  ){
				
				for(int x=0; x<i; x++)
					for(int y=0; y<j; y++)
						 
						XYZ.Image[x][y]=Image[x][y]*b + (1-b)*Debuggers.Image[x][y];
					
				
	
	
			char X[10];
			itoa ( count,X, 10 );
			XYZ.Save(  BaseFileName +X +".pgm"  );
			count++  ;
			if(0> b-SS && b-SS> -SS)
			   b=0;
	     	}
	    	
	    	
			
			
    }

    
	    int load(string File_Name){
	    	ifstream IN(File_Name.c_str());
	        int a=File_Name.length();
	        if(File_Name[a-4]!= '.'|| File_Name[a-3]!= 'p'|| File_Name[a-2]!= 'g'|| File_Name[a-1]!= 'm' )
			    return 1;
	        if(!IN)
	           return 2;
	        string MagicNum;
			string Comment;
			getline(IN, MagicNum);
			getline(IN, Comment);
	        IN>>Cols>>Rows>>Maximum;
			for(int i=0; i<Rows; i++)
			{
				for(int j=0; j<Cols; j++){
					IN>>Image[i][j];
				}
			}
	        IN.close();
	        loaded = true;
	        return 0;

	        /*
	            Function to load data of an image from an ASCII  pgm file into the structure variables
	        */

	    }

	    int Save(string File_Name){
	    	ofstream OUT(File_Name.c_str());
	    	if(!OUT)
	    	    return 2;
	        int b=File_Name.length();
	        if(File_Name[b-4]!= '.'|| File_Name[b-3]!= 'p'|| File_Name[b-2]!= 'g'|| File_Name[b-1]!= 'm' )
			    return 1;
			      else
				  {

	    	OUT<<"P2"<<endl;
	    	OUT<<"# The Debuggers\n";
	        OUT<<Cols<<" "<<Rows<<endl<<Maximum<<endl;
			for(int i=0; i<Rows; i++)
			{
				for(int j=0; j<Cols; j++){
				    OUT<<Image[i][j]<<" ";
				}
				OUT<<endl;
			}
		}
			OUT.close();
			return 0;
	        /*
	            Function to Save the data of an Image available in the structure into an ASCII pgm file.
	        */

	    }


	    void Rotate(grayImage& Debuggers, double angle = 90, int aboutx = 0, int abouty = 0 ){
	        
			for(int x= 0; x  <  MaxRows;x++  )
	        	for( int y=0;  y<MaxCols ;y++  ){
	        		
	        		int l= x- aboutx;
	        		int m= y-abouty;
	        		
	        		
	        		double p= cos(angle*( 3.14/180.0));
	        		
					double f=sin( angle*( 3.14/180.0));
					
					int	r= (l*p)  -(m *f)+aboutx;
	        		int	c=(m *p)   +   (l*f) +abouty ;
	        			if(r>0  && r<MaxRows&& c> 0 &&c <MaxCols)
	        			
	        				Debuggers.Image[x][y]= Image[r][c] ;
	        				
						
	        				
				}
			
			
		    Debuggers.Rows= MaxRows ;Debuggers.Cols= MaxCols;
		    
			Debuggers.Maximum = Maximum  ;Debuggers.loaded =true;
			
			
	    }

	    void Flip(int HorizontalOrVertical=0){


	    	if(HorizontalOrVertical==0){
	    		FlipVerttical();
			}
			if(HorizontalOrVertical==1){
				FlipHorizontal();
			}
	        
	    }

	    void Negative(){
	    	int Max   =   255;
	    	for(int c=0; c<Cols; c++)
	    	{
	    		for(int r  =  0; r   <  Rows;    r++)
	    		{
	    			Image[r][c] =    Max   - Image[r][c]  ;

				}
			}


	    }

	    void changeBrightness(int amount){
	    	int Max     =   255;
	    	int Min     =    0;
	    	for( int c   =  0; c <   Cols;    c++)
	    	{
	    		for( int r   =   0; r   <  Rows;    r++)
	    		{
	    			Image[r][c] +=     amount;
	    			if(  Image[r][c]  >  Max   )   
			        {
				        Image[r][c]   =  Max;
			        }
			        if(   Image[r][c]   <   Min   )
			        {
				        Image[r][c] =     Min;
			        }
				}
			}

	    }

	    void Quantize(grayImage& Debuggers, int level){
        int SS    =    Maximum/level;
        for(  int m    = 0; m   <   Rows;   m++   )
        {
        	for(   int n    =  0; n<   Cols ; n++   )  
        	{
        	   Debuggers.Image[m][n]     =  Image[m][n]/SS*SS    +     SS/2;	
			}
		}
		
		Debuggers.Rows =     Rows;
		Debuggers.Cols =   Cols;
		Debuggers.Maximum =      Maximum;
        }

	  void medianFilter(grayImage& Debuggers, int filterSize = 3){
        int  Median;
        int A[MaxRows];
    	int F    =    filterSize*filterSize;
    	int a   =     filterSize/2;
    	for(int j  =  a; j   <  Rows-a;    j++) 
    	{
            for(  int k =   a; k   <  Cols-a;    k++ )
    		{
    			int n  =  0;
    		    for(int   b =     j-a; b  <=   j+a; b++    )
    		    {
    		    	for(int c  =   k-a; c<=  k+a; c++   )
    		    	{
    		    		A[n] =   Image[b][c];
    		    		n++;
					}

				}
				bubble(A, F);
				
				if(F%2 ==   0)		
				{
					int s   =     F/2;
					Median=       (A[s]+A[s-1])/2;
				}
				else
				{
					int g =   F/2;
					Median   =   A[g];
				}					    
				Debuggers.Image[j][k] =   Median;

			}
		}
		Debuggers.Rows =   Rows;
		Debuggers.Cols =  Cols;
		Debuggers.Maximum =    Maximum;
    }

       void meanFilter(grayImage& Debuggers, int filterSize = 3){
    	int  Mean;
    	int  F   =   filterSize*filterSize;
    	int a =   filterSize/2;

    	for(int   j  =  a; j<   Rows - a;   j++  ) 
    	{
            for(int k  = a; k   <  Cols -a;    k++)
    		{
    		    int Sum   =    0;
    		    for(int b =   j  -  a; b  <=   j+a;    b++)
    		    {
    		    	for(int c =   k  - a; c  <=  k + a; c++   )
    		    	{
    		    		Sum   =  Sum +   Image[b][c];
					}

				}
				Mean   =   Sum/F;
				Debuggers.Image[j][k]   =    Mean;

			}
		}
		Debuggers.Rows =     Rows;
		Debuggers.Cols = Cols;
		Debuggers.Maximum =     Maximum;
		
    }


	    void Resize(grayImage& Debuggers,int NewRows, int NewColumns){
	    	
	        double ssr =NewRows*1.0 /Rows;
	        
	        double ssc= NewColumns*1.0/ Cols;
	        
	        

	        for(int x=0;x<NewRows;x++)
	        	for(int y=0;y<NewColumns;y++){
	        		
	        		
	        		int r = x/ssr  ;
	        		
	        		int n=  y /ssc;
	        		
	        		
	        		Debuggers.Image[x][y]   = Image[r][n];
	        		
	        	}
	        	
	         Debuggers.Rows   = NewRows ;
	    	Debuggers.Cols =   NewColumns;
	        Debuggers.Maximum   = Maximum ;
			

	    }

	    void Resize(grayImage& Debuggers,double Ratio){
	        /*
	            Change the rows and columns by the ratio
	        */
	        int NewRows  =Ratio* Rows;
	        
	        int NewColumns =Ratio *Cols ;
	        
	        
	        for(int i=0;i<NewRows;i++){
	        	for(int j=0;j<NewColumns;j++)
				{
					
	        		int r=i/Ratio  ;
	        		
	        		int n=j  /Ratio;
	        		
	        		
	        		Debuggers.Image[i][j] = Image[r][n];
	        		
	        	}
	         Debuggers.Rows = NewRows ;
	    	Debuggers.Cols =NewColumns;
			Debuggers.Maximum= Maximum ;
			}
	        
	    }

	  void Transform(grayImage& Debuggers, double Matrix[3][3]){
    	double p,s,m;
    	int K,L,i,j;
    	int r =  0;
    	int M=1;
        for( K  = 0; K   <Rows;    K++)
        {
        	for(  L =  0; L  <  Cols;    L++)
        	{
        		p= (Matrix[r][r]  *   K) + (Matrix[r][r+1] *  L) +     (Matrix[r][r+2] * M);
        		s= (Matrix[r+1][r]*    K) + (Matrix[r+1][r+1]  *L) +     (Matrix[r+1][r+2]* M);
        		m= (Matrix[r+2][r]   *  K) + (Matrix[r+2][r+1]  *  L) + ( Matrix[r+2][r+2]* M);
        		if(m   !=  0)
        		{
        			j=  s/m;
        			i  = p/m;
        			if(j>=0    &&    j< MaxCols )
        			{
        				if( i   >=   0 &&   i<MaxRows)
						{
        					Debuggers.Image[i][j]   =  Image[K][L];
						}
        				
        				
        				
					}
				}
    
			}
		}
		Debuggers.Rows =    Rows;
		Debuggers.Cols = Cols;
		Debuggers.Maximum =   Maximum;
    }
    
    void Crop(grayImage& Debuggers, int top, int bottom, int left, int right){
    	int k,z;
    	for(int i  =  top, k  =  0; i   <   Rows-bottom;   i++,  k++)
    	{
    		for(int  j = left, z  =  0; j   <  Cols-right;   j++,    z++)
    		{
    			
    			Debuggers.Image[k][z]   =     Image[i][j];
			}
		}
		Debuggers.Rows =     Rows;
		Debuggers.Cols =    Cols;
		Debuggers.Maximum =Maximum;
	}

    void Filter(grayImage& Debuggers, double Mask[3][3]){
    	int A[50];
        int filterSize   =   3;
    	int F=     filterSize*filterSize;
    	int a   =filterSize/2;
    	
    	for(int   j  =   a; j  <   Rows -a;    j++) 
    	{
            for(int k = a; k   <Cols-a;   k++   )
    		{
    			int n =  0;
    		    for(int b = j  -  a; b  <=j+a;   b++)
    		    {
    		    	for(int c =  k-a; c  <=k+a;   c++)
    		    	{
    		    		
    		    		A[n]  =  Image[b][c];
    		    		n++;
					}

				}
				int Sum =  0;
				n=  0;
				for(int s=  0; s  <3  ;   s++)
				{
					for(int p =  0; p <   3;   p++)
					{
						Sum=   Sum +(A[n] * Mask[s][p]);
						n++;
					}
				}
				if( Sum  >    255)
				{
					Debuggers.Image[j][k]  =  255;
				}
				else
				{
					Debuggers.Image[j][k]=   Sum;
				}

			}
		}
		Debuggers.Rows = Rows;
		Debuggers.Cols =     Cols;
		Debuggers.Maximum = Maximum;
                
        
        
    }

    void DerivativeImage(grayImage& Debuggers){
    	int A[50];
    	int B[50]={-1,0,1,-1,0,1,-1,0,1};
    	int C[50]={-1,-1,-1,0,0,0,1,1,1};
        int filterSize=  3;
    	int F =   filterSize*filterSize;
    	int a =  filterSize/2;
    	
    	for(int  j=  a; j  <Rows-a;  j++) 
    	{
            for(int k =   a; k  < Cols-a; k++  )
    		{
    			int n=  0;
    		    for(int b = j  -  a; b  <=  j+a;   b++)
    		    {
    		    	for(int c= k-a; c  <=k+a; c++  )
    		    	{
    		    		
    		    		A[n]=   Image[b][c];
    		    		n++;
					}

				}
				int Sum1=  0;
				
				for(int p =  0; p  <  9;   p++)
				{
					Sum1=Sum1 +  (A[p]*B[p]);
				}
				int Sum2=  0;
				
				for(int p=  0; p  <  9; p++)
				{
					Sum2= Sum2 +  (A[p]*C[p]);
				}
				
				int S=  (Sum1*Sum1) + (Sum2*Sum2);
				int Sum=   sqrt(S);
				if(  Sum   >  255)
				{
					Debuggers.Image[j][k]   =  255;
				}
				else
				{
					Debuggers.Image[j][k]=  Sum;
				}

			}
		}
		Debuggers.Rows = Rows;
		Debuggers.Cols =    Cols;
		Debuggers.Maximum =      Maximum;
    	
    	
    	


    }


	private:
	void bubble(int A[], int F){
	   for(int l=  1 ; l < F ; ++l)
	   {
			for(int q  =  0; q  <  (F-l) ;  ++q)
				if(  A[q]  >  A[q+1])
				{
					int temp  =A[q];
					A[q]  =A[q+1];
					A[q+1]=  temp;
				}
		}
	}
	    void FlipHorizontal(){
	    	for(int j=0 ; j <  Rows ; j++)
	        {
		        for( int  k = 0 ; k  <   Cols/2 ;  k++)
	            {
	                int A =Image[j][Cols-k];
	                Image[j][Cols-k] = Image[j][k];
	                Image[j][k]   = A;
	     	   }
		    }

	    }

	    void FlipVerttical(){
	    	for(int j=0 ; j<Cols ; j++)
	        {
		        for( int  k = 0 ; k  <  Rows/2 ;  k++)
	            {
	                int A = Image[Rows-k][j];
	                Image[Rows-k][j]  = Image[k][j];
	                Image[k][j] = A;
	     	   }
		    }

	    }

	    void Fill(int L, int T, int R, int B, int FillValue){
	        for(int i = T; i<= B; i++)
	            for(int j = L; j  <= R; j++)
	                Image[i][j] =  FillValue;
	    }

	    unsigned short Image[MaxRows][MaxCols];
	    int Rows, Cols, Maximum;
	    bool loaded;
	};

	int main(){
		 
	    string Menu = "\n0.Combine Side By Side\n1.Combine Top to Bottom\n2.Fade In\n3.Rotate\n4.Negative\n5.Flip\n6.Change Brightness\n7.Quantize\n8.Median Filter\n9.Mean Filter\n10.Resize by New Rows and columns\n11.Resize by Ratio\n12.Transform\n13.Crop\n14.Filter\n15.Derivative\n16.Exit.";
	    cout<<Menu;
	    int Choice;
	    grayImage GM, GM2, New;
	    string pgm;
	    string pgm2;
		
		
	    do{
	    	cout<<"\nWhat's your Choice \n";
		    cin>>Choice;
		    if(Choice !=16){
		    	cout<<"\nEnter your pgm image for example xyz.pgm\n";
	    		cin>>pgm;
	    		GM.load(pgm);
			}
	    	
			
			if(Choice == 0){
				cout<<"Enter your 2nd pgm image\n ";
				cin>>pgm2;
				GM2.load(pgm2);
				cout<<"Enter the size of fill value\n";
				int a;
				cin>>a;
		    	GM.combineSideBySide(GM2,a);
		    	
			}
			
			else if(Choice == 1){
				cout<<"Enter your 2nd pgm image\n ";
				cin>>pgm2;
				GM2.load(pgm2);
				cout<<"Enter the size of fill value : ";
				int a;
				cin>>a;
		    	GM.combineTopToBottom(GM2, 255);
		    	
				
			}
			else if(Choice == 2){
				
				cout<<"Enter your 2nd pgm image\n ";
				cin>>pgm2;
				GM2.load(pgm2);
				int Frames,Seconds;
				string BaseFileName;
				cout<<"Enter frames : ";
				cin>>Frames;
				cout<<"Enter seconds : ";
				cin>>Seconds;
				GM.FadeIn(GM2, Frames, Seconds,"C:\\Users\\hp\\Desktop\\project 1\\second\\" );
				
			}
		
			else if(Choice == 3){
				int angle,aboutx,abouty;
				cout<<"Enter angle : ";
				cin>>angle;
				cout<<"Enter x-axis : ";
				cin>>aboutx;
				cout<<"Enter y-axis : ";
				cin>>abouty;
				GM.Rotate(New,angle, aboutx, abouty);
				
			}
			else if(Choice == 4){
				GM.Negative();
			}
			else if(Choice == 5){
				cout<<"Press 0 for Vertical and 1 for Horizontal Flip\n";
				int a;
   				cin>>a;
				GM.Flip(a);
			}
			else if(Choice == 6){
				int amount;
				cout<<"Enter the value of brightness : ";
				cin>>amount;
				GM.changeBrightness(amount);
			}
			else if(Choice == 7){
				int Level;
				cout<<"Enter level of quantization : ";
				cin>>Level;
				GM.Quantize(New,Level);
			}
			else if(Choice == 8){
				int filterSize;
				cout<<"Enter Filter Size : ";
				cin>>filterSize;
				GM.medianFilter(New,filterSize);
			}
			else if(Choice == 9){
				int filterSize;
				cout<<"Enter Filter Size : ";
				cin>>filterSize;
				GM.meanFilter(New,filterSize);
			}
			else if(Choice == 10){
				int NewRows,NewColumns;
				cout<<"Enter New Rows : ";
				cin>>NewRows;
				cout<<"Enter New Columns : ";
				cin>>NewColumns;
				GM.Resize(New,NewRows,NewColumns);
			}
			else if(Choice == 11){
				double Ratio;
				cout<<"Enter ratio of new image : ";
				cin>>Ratio;
				GM.Resize(New,Ratio);
			}
			else if(Choice == 12){
				cout<<"Enter Matrix of 3by3 : ";
				double Matrix[3][3];
				for(int i=0; i<3; i++)
				{
					for(int j=0; j<3; j++)
					{
						cin>>Matrix[i][j];
					}
				}
				GM.Transform(New, Matrix);
			}
			else if(Choice == 13){
				int top,bottom,left,right;
				cout<<"Enter top : ";
				cin>>top;
				cout<<"Enter bottom : ";
				cin>>bottom;
				cout<<"Enter left : ";
				cin>>left;
				cout<<"Enter right : ";
				cin>>right;
				GM.Crop(New, top, bottom, left, right);
			}
			else if(Choice == 14){
				cout<<"Enter Mask of 3by3 \n";
				double Mask[3][3];
				for(int i=0; i<3; i++)
				{
					for(int j=0; j<3; j++)
					{
						cin>>Mask[i][j];
					}
				}
				GM.Filter(New,Mask);
			}
			else if(Choice == 15){
				GM.DerivativeImage(New);
			}
				
	if(Choice ==0 || Choice == 1 || Choice == 2 ||Choice==4|| Choice == 5 || Choice == 6)
		GM.Save("The Debuggers.pgm");
	else
		New.Save("The Debuggers.pgm");
		
	if(Choice !=16){
		cout<<"\nYour file is ready\n\n";
	}
	
	}while(Choice != 16);
	cout<<"May Allah bless you! ";
	return 0;

  
}
