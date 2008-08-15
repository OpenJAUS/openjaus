#ifndef TRANSPORTABLE_H_
#define TRANSPORTABLE_H_

class Transportable
{
public:
	virtual ~Transportable(void);
	
	virtual int toBuffer(unsigned char *buffer, int bufferSizeBytes) = 0;

	virtual int fromBuffer(unsigned char *buffer, int bufferSizeBytes) = 0;
		
	virtual int getSizeBytes(void) = 0; 
	
	//virtual bool isFragment(void);
	
	//virtual bool isFragmentOf(Transportable otherFragment);
	
	//virtual bool addFragment(Transportable otherFragment);
	
	//virtual List<Transportable> toFragments(int maxTransmissionUnit);
	
};

#endif /*TRANSPORTABLE_H_*/
