/***************************** Include Files *********************************/

#include "ma_ff_timer.h"

/************************** Constant Definitions *****************************/
/*
 * The following constant determines which timer counter of the device that is
 * used for this example, there are currently 2 timer counters in a device
 * and this example uses the first one, 0, the timer numbers are 0 based
 */
#define INTC		    XIntc
#define INTC_HANDLER	XIntc_InterruptHandler

/*
 * The following constant is used to set the reset value of the timer counter,
 * making this number larger reduces the amount of time this example consumes
 * because it is the value the timer counter is loaded with when it is started
 */
/*
 *  timer clock is 10ns period so for 1ms timer must count 100000
 *  LogiCORE IP AXI Timer v1.03a page 7 say timer value + 2
 */
//#define RESET_VALUE	 0xFFFFFFFF - 100000 + 2
#define RESET_VALUE	 0xFFFFFFFF - 200000 + 2

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/************************** Function Prototypes ******************************/

static int TmrCtrSetupIntrSystem(INTC* IntcInstancePtr, XTmrCtr* InstancePtr,
		u16 DeviceId, u16 IntrId, u8 TmrCtrNumber);

void TimerCounterHandler(void *CallBackRef, u8 TmrCtrNumber);

void TmrCtrDisableIntr(INTC* IntcInstancePtr, u16 IntrId);
/************************** Variable Definitions *****************************/INTC InterruptController; /* The instance of the Interrupt Controller */
XTmrCtr TimerCounterInst; /* The instance of the Timer Counter */

/*****************************************************************************/
/**
 * This function does a minimal test on the timer counter device and driver as a
 * design example.  The purpose of this function is to illustrate how to use the
 * XTmrCtr component.  It initializes a timer counter and then sets it up in
 * compare mode with auto reload such that a periodic interrupt is generated.
 *
 * This function uses interrupt driven mode of the timer counter.
 *
 * @param	IntcInstancePtr is a pointer to the Interrupt Controller
 *		driver Instance
 * @param	TmrCtrInstancePtr is a pointer to the XTmrCtr driver Instance
 * @param	DeviceId is the XPAR_<TmrCtr_instance>_DEVICE_ID value from
 *		xparameters.h
 * @param	IntrId is XPAR_<INTC_instance>_<TmrCtr_instance>_INTERRUPT_INTR
 *		value from xparameters.h
 * @param	TmrCtrNumber is the number of the timer to which this
 *		handler is associated with.
 *
 * @return	XST_SUCCESS if the Test is successful, otherwise XST_FAILURE
 *
 * @note		This function contains an infinite loop such that if interrupts
 *		are not working it may never return.
 *
 *****************************************************************************/
int ma_timer_init(void) {
	int Status;
	//int LastTimerExpired = 0;

	/*
	 * Initialize the timer counter so that it's ready to use,
	 * specify the device ID that is generated in xparameters.h
	 */
	Status = XTmrCtr_Initialize(&TimerCounterInst, TMRCTR_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Perform a self-test to ensure that the hardware was built
	 * correctly, use the 1st timer in the device (0)
	 */
	Status = XTmrCtr_SelfTest(&TimerCounterInst, 0);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Connect the timer counter to the interrupt subsystem such that
	 * interrupts can occur.  This function is application specific.
	 */
	Status = TmrCtrSetupIntrSystem(&InterruptController, &TimerCounterInst,
			TMRCTR_DEVICE_ID, TMRCTR_INTERRUPT_ID, 0);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Setup the handler for the timer counter that will be called from the
	 * interrupt context when the timer expires, specify a pointer to the
	 * timer counter driver instance as the callback reference so the handler
	 * is able to access the instance data
	 */
	XTmrCtr_SetHandler(&TimerCounterInst, TimerCounterHandler,
			&TimerCounterInst);

	/*
	 * Enable the interrupt of the timer counter so interrupts will occur
	 * and use auto reload mode such that the timer counter will reload
	 * itself automatically and continue repeatedly, without this option
	 * it would expire once only
	 */
	XTmrCtr_SetOptions(&TimerCounterInst, 0,
			XTC_INT_MODE_OPTION | XTC_AUTO_RELOAD_OPTION);

	/*
	 * Set a reset value for the timer counter such that it will expire
	 * eariler than letting it roll over from 0, the reset value is loaded
	 * into the timer counter when it is started
	 */
	XTmrCtr_SetResetValue(&TimerCounterInst, 0, RESET_VALUE);

	/*
	 * Start the timer counter such that it's incrementing by default,
	 * then wait for it to timeout a number of times
	 */
	XTmrCtr_Start(&TimerCounterInst, 0);

	return XST_SUCCESS;
}

/*****************************************************************************/
/**
 * This function is the handler which performs processing for the timer counter.
 * It is called from an interrupt context such that the amount of processing
 * performed should be minimized.  It is called when the timer counter expires
 * if interrupts are enabled.
 *
 * This handler provides an example of how to handle timer counter interrupts
 * but is application specific.
 *
 * @param	CallBackRef is a pointer to the callback function
 * @param	TmrCtrNumber is the number of the timer to which this
 *		handler is associated with.
 *
 * @return	None.
 *
 * @note		None.
 *
 ******************************************************************************/
void TimerCounterHandler(void *CallBackRef, u8 TmrCtrNumber) {
	//XTmrCtr *InstancePtr = (XTmrCtr *)CallBackRef;

	/*
	 * Check if the timer counter has expired, checking is not necessary
	 * since that's the reason this function is executed, this just shows
	 * how the callback reference can be used as a pointer to the instance
	 * of the timer counter that expired, increment a shared variable so
	 * the main thread of execution can see the timer expired
	 */
//	if (XTmrCtr_IsExpired(InstancePtr, TmrCtrNumber)) {
//		TimerExpired++;
//		if(TimerExpired == 3) {
//			XTmrCtr_SetOptions(InstancePtr, TmrCtrNumber, 0);
//		}
//	}
	//disk_timerproc();
}

/*****************************************************************************/
/**
 * This function setups the interrupt system such that interrupts can occur
 * for the timer counter. This function is application specific since the actual
 * system may or may not have an interrupt controller.  The timer counter could
 * be directly connected to a processor without an interrupt controller.  The
 * user should modify this function to fit the application.
 *
 * @param	IntcInstancePtr is a pointer to the Interrupt Controller
 *		driver Instance.
 * @param	TmrCtrInstancePtr is a pointer to the XTmrCtr driver Instance.
 * @param	DeviceId is the XPAR_<TmrCtr_instance>_DEVICE_ID value from
 *		xparameters.h.
 * @param	IntrId is XPAR_<INTC_instance>_<TmrCtr_instance>_VEC_ID
 *		value from xparameters.h.
 * @param	TmrCtrNumber is the number of the timer to which this
 *		handler is associated with.
 *
 * @return	XST_SUCCESS if the Test is successful, otherwise XST_FAILURE.
 *
 * @note		This function contains an infinite loop such that if interrupts
 *		are not working it may never return.
 *
 ******************************************************************************/
static int TmrCtrSetupIntrSystem(INTC* IntcInstancePtr,
		XTmrCtr* TmrCtrInstancePtr, u16 DeviceId, u16 IntrId, u8 TmrCtrNumber) {
	int Status;

	/*
	 * Initialize the interrupt controller driver so that
	 * it's ready to use, specify the device ID that is generated in
	 * xparameters.h
	 */
	Status = XIntc_Initialize(IntcInstancePtr, INTC_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
	/*
	 * Connect a device driver handler that will be called when an interrupt
	 * for the device occurs, the device driver handler performs the specific
	 * interrupt processing for the device
	 */
	Status = XIntc_Connect(IntcInstancePtr, IntrId,
			(XInterruptHandler) XTmrCtr_InterruptHandler,
			(void *) TmrCtrInstancePtr);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Start the interrupt controller such that interrupts are enabled for
	 * all devices that cause interrupts, specific real mode so that
	 * the timer counter can cause interrupts thru the interrupt controller.
	 */
	Status = XIntc_Start(IntcInstancePtr, XIN_REAL_MODE);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	/*
	 * Enable the interrupt for the timer counter
	 */
	XIntc_Enable(IntcInstancePtr, IntrId);

	/*
	 * Initialize the exception table.
	 */
	Xil_ExceptionInit();

	/*
	 * Register the interrupt controller handler with the exception table.
	 */
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
			(Xil_ExceptionHandler) INTC_HANDLER, IntcInstancePtr);

	/*
	 * Enable non-critical exceptions.
	 */
	Xil_ExceptionEnable();

	return XST_SUCCESS;
}

/******************************************************************************/
/**
 *
 * This function disables the interrupts for the Timer.
 *
 * @param	IntcInstancePtr is a reference to the Interrupt Controller
 *		driver Instance.
 * @param	IntrId is XPAR_<INTC_instance>_<Timer_instance>_VEC_ID
 *		value from xparameters.h.
 *
 * @return	None.
 *
 * @note		None.
 *
 ******************************************************************************/
void TmrCtrDisableIntr(INTC* IntcInstancePtr, u16 IntrId) {
	/*
	 * Disable the interrupt for the timer counter
	 */
	XIntc_Disable(IntcInstancePtr, IntrId);

	return;
}

/******************************************************************************/

