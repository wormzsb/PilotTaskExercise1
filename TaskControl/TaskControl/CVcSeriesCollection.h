// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

//#import <mschrt20.ocx> no_namespace
#import "MSCHRT20.OCX" no_namespace
// CVcSeriesCollection wrapper class

class CVcSeriesCollection : public COleDispatchDriver
{
public:
	CVcSeriesCollection(){} // Calls COleDispatchDriver default constructor
	CVcSeriesCollection(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CVcSeriesCollection(const CVcSeriesCollection& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// Attributes
public:

	// Operations
public:


	// IVcSeriesCollection methods
public:
	LPUNKNOWN get__NewEnum()
	{
		LPUNKNOWN result;
		InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
		return result;
	}
	long Count()
	{
		long result;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Item(short Index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
		return result;
	}
	LPDISPATCH get__Item(short Index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Index);
		return result;
	}

	// IVcSeriesCollection properties
public:

};
