#ifndef TRANSPORTABLE_H_
#define TRANSPORTABLE_H_

class Transportable
{
public:
	virtual ~Transportable(void);
	
	virtual int toBuffer(char *buffer, int bufferSizeBytes);

	virtual int fromBuffer(char *buffer, int bufferSizeBytes);
		
	virtual int sizeBytes(void); 
	
	virtual bool isFragment(void);
	
	virtual bool isFragmentOf(Transportable otherFragment);
	
	virtual bool addFragment(Transportable otherFragment);
	
	virtual List<Transportable> toFragments(int maxTransmissionUnit);
	
};

#endif /*TRANSPORTABLE_H_*/
