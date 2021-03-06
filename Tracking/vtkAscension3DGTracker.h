/*=========================================================================

  Program:   Tracking for VTK
  Module:    $RCSfile: vtkAscension3DGTracker.h,v $
  Creator:   Andrew Wiles <awiles@ndigital.com>
  Language:  C++
  Author:    $Author: awiles $
  Date:      $Date: 2011/06/07  $
  Version:   $Revision: 1.0 $

==========================================================================

Copyright (c) 2000-2004
All rights reserved.

THE COPYRIGHT HOLDERS AND/OR OTHER PARTIES PROVIDE THE SOFTWARE "AS IS"
WITHOUT EXPRESSED OR IMPLIED WARRANTY INCLUDING, BUT NOT LIMITED TO,
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE.  IN NO EVENT SHALL ANY COPYRIGHT HOLDER OR OTHER PARTY WHO MAY
MODIFY AND/OR REDISTRIBUTE THE SOFTWARE UNDER THE TERMS OF THIS LICENSE
BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, LOSS OF DATA OR DATA BECOMING INACCURATE
OR LOSS OF PROFIT OR BUSINESS INTERRUPTION) ARISING IN ANY WAY OUT OF
THE USE OR INABILITY TO USE THE SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGES.

=========================================================================*/
// .NAME vtkAscension3DGTracker - VTK interface for the 3DG trakStar, medSafe and driveBay
// .SECTION Description
// The vtkAscension3DGTracker class provides an  interface to the 3DG trakStar, 
// medSafe and driveBay magnetic tracking system.
// .SECTION Caveats
// This class refers to ports 1,2,3,A,B,C as ports 0,1,2,3,4,5
// .SECTION see also
// vtkTrackerTool vtkFlockTracker vtkMicroBirdTracker

#ifndef __vtkAscension3DGTracker_h
#define __vtkAscension3DGTracker_h

#include "vtkTracker.h"
//#ifdef Ascension3DG_MedSafe
//#include "ATC3DGm.h"
//#else /* Ascension3DG_MedSafe */
//#include "ATC3DG.h"
//#endif /* Ascension3DG_MedSafe */

#include "vtkAscension3DGConfig.h"

// the number of tools the ascension can handle

#define VTK_3DG_REPLY_LEN 2048

class VTK_EXPORT vtkAscension3DGTracker : public vtkTracker
{
  public:

  static vtkAscension3DGTracker *New();


  vtkTypeMacro(vtkAscension3DGTracker,vtkTracker);
  void PrintSelf(ostream& os, vtkIndent indent);
 
  // Description:
  // Probe to see if the tracking system is present on the
  // specified serial port.  If the SerialPort is set to -1,
  // then all serial ports will be checked.
  int Probe();
  int GetSerialPort();
  int SetSerialPort(int port);


  // Description:
  // Get an update from the tracking system and push the new transforms
  // to the tools.  This should only be used within vtkTracker.cxx.
  void InternalUpdate();

  //***************************************************************************
  // SYSTEM CONFIGURATION
  //***************************************************************************
  int  ReadCurrentSettings( vtkAscension3DGConfig *config);
  inline vtkAscension3DGConfig* GetCurrentSettings() {return this->m_TrackerCurrentConfig;}
  int  RestoreConfiguration(char * filename);
  int  SaveConfiguration(char * filename);

  int  SetPowerLineFrequency(double pl);
  int  SetAGCMode(AGC_MODE_TYPE agc);
  int  SetMeasurementRate(double rate);
  int  SetMaximumRange(double range);
  int  SetMetric(bool metric);
  //int  SetTransmitter(short tx);

protected:
  int  InternalSetPowerLineFrequency(double pl);
  int  InternalSetAGCMode(AGC_MODE_TYPE agc);
  int  InternalSetMeasurementRate(double rate);
  int  InternalSetMaximumRange(double range);
  int  InternalSetMetric(bool metric);
  int  InternalSetTransmitter(short tx);

public: 
  int			GetPowerLineFrequency();
  AGC_MODE_TYPE GetAGCMode();
  double		GetMeasurementRate( );
  double		GetMaximumRange();
  bool			GetMetric();
  short			GetTransmitter( );

  //***************************************************************************
  // BOARD CONFIGURATION
  //***************************************************************************
  int  GetNumberOfBoards() { return this->m_TrackerCurrentConfig->m_SystemConfig->numberBoards; }
  int  GetNumberOfSensors() { return  this->m_TrackerCurrentConfig->m_SystemConfig->numberSensors; }
  int  GetNumberOfTransmitter() { return  this->m_TrackerCurrentConfig->m_SystemConfig->numberTransmitters; }

  //***************************************************************************
  // SENSOR CONFIGURATION
  //***************************************************************************
  int  SetSensorFilterACWideNotch(int sensorID, BOOL buffer);
  int  SetSensorFilterACNarrowNotch(int sensorID, BOOL buffer);
  int  SetSensorFilterDCAdaptive(int sensorID,double buffer);
  int  SetSensorFilterLargeChange(int sensorID, BOOL buffer);

//BTX
  int  SetSensorDataFormat(int sensorID, DATA_FORMAT_TYPE buffer);
  int  SetSensorAngleAlign(int sensorID, DOUBLE_ANGLES_RECORD buffer);
  int  SetSensorHemisphere(int sensorID,HEMISPHERE_TYPE buffer);
  int  SetSensorFilterAlphaParamaters(int sensorID,ADAPTIVE_PARAMETERS buffer);
  int  SetSensorQuality(int sensorID,QUALITY_PARAMETERS buffer);
//ETX

//BTX
  DATA_FORMAT_TYPE		GetSensorDataFormat(int sensorID);
  DOUBLE_ANGLES_RECORD	GetSensorAngleAlign(int sensorID);
  HEMISPHERE_TYPE		GetSensorHemisphere(int sensorID);
  BOOL					GetSensorFilterACWideNotch(int sensorID);
  BOOL					GetSensorFilterACNarrowNotch(int sensorID);
  double				GetSensorFilterDCAdaptive(int sensorID);
  ADAPTIVE_PARAMETERS	GetSensorFilterAlphaParamaters(int sensorID);
  BOOL					GetSensorFilterLargeChange(int sensorID);
  QUALITY_PARAMETERS	GetSensorQuality(int sensorID);
//ETX


  // GET/SET BOARD PARAMATERS
  // int GetBirdError()
  // DEVICE_STATUS GetSensorStatus(unsigned short sensorID);
  // DEVICE_STATUS GetTransmitterStatus(unsigned short transmitterID);
  // DEVICE_STATUS GetBoardStatus(unsigned short boardID);
  // DEVICE_STATUS GetBoardStatus(unsigned short boardID);
  // DEVICE_STATUS GetSystemStatus();

  //***************************************************************************
  // TRANSMITTER CONFIGURATION
  //***************************************************************************
  int  SetTransmitterXYZReferenceFrame(int transmitterID,BOOL buffer);
  int  SetTransmitterReferenceFrame(int transmitterID, DOUBLE_ANGLES_RECORD buffer);


  BOOL					GetTransmitterXYZReferenceFrame(int transmitterID);
//BTX
  DOUBLE_ANGLES_RECORD	GetTransmitterReferenceFrame(int transmitterID);
  DEVICE_TYPES GetSensorType();
//ETX

  char * GetBoardModel();
  unsigned short GetBoardFirmwareRevision();
  unsigned short GetBoardRevision();
  unsigned short GetBoardFirmwareNumber();
  int SetSensorOnly();
  int SetSensorAndTransmitter();
  int GetAGCType();
  int SetSensorAngleAlign(int sensorID, double angles[3]);

  int  SetSensorHemisphere(int sensorID,int hemisphere);
  int  SetSensorFilterACWideNotch(int sensorID, bool buffer);
  int  SetSensorFilterACNarrowNotch(int sensorID,  bool buffer);
  int  SetSensorFilterAlphaParamaters(int sensorID,unsigned short alphaMin[7], unsigned short alphaMax[7], unsigned short vm[7], bool alphaOn);
  int  SetSensorQuality(int sensorID, unsigned short slope, unsigned short offset, unsigned short sensitivity, unsigned short filter_alpha);
  double * GetSensorAngleAlignment(int sensorID);
  char * GetSensorHemisphereName(int sensorID);
  unsigned short * GetSensorFilterAlphaMax(int sensorID);
  unsigned short * GetSensorFilterAlphaMin(int sensorID);
  unsigned short * GetSensorFilterVM(int sensorID);
  int GetSensorFilterAlphaOn(int sensorID);
  unsigned short * GetSensorQualityValues(int sensorID);
  unsigned short GetSensorQualityErrorSlope(int sensorID);
  unsigned short GetSensorQualityErrorOffset(int sensorID);
  unsigned short GetSensorQualityErrorSensitivity(int sensorID);
  unsigned short GetSensorQualityFilterAlpha(int sensorID);
  double * GetTransmitterReferenceFrameAngle(int transmitterID);
  int SetTransmitterReferenceFrame(int transmitterID, double azimuth, double elevation, double roll);
  int SetTransmitterXYZReferenceFrame(int transmitterID, bool buffer);
  int SetSensorFilterLargeChange(int sensorID, bool buffer);

  // Data collection options.
  inline void SetUseDefaultSettings(bool bUseDefault) {this->m_bUseDefaultSystemSettings = bUseDefault;}
  inline void SetUseSynchronousRecord(bool bSync) {this->m_bUseSynchronous = bSync;}
  inline void SetUseAllSensors(bool bUseAllSensors) {this->m_bUseAllSensors = bUseAllSensors;}

protected:
  vtkAscension3DGTracker();
  ~vtkAscension3DGTracker();
  void errorHandler(int error, char* func=0);
  void TransformToMatrixd(const DOUBLE_ALL_TIME_STAMP_Q_RECORD trans, double matrix[16]);
  void RelativeTransform(const DOUBLE_ALL_TIME_STAMP_Q_RECORD aRecord, const DOUBLE_ALL_TIME_STAMP_Q_RECORD *bRecord, DOUBLE_ALL_TIME_STAMP_Q_RECORD cRecord);

  // Description:
  // Initialize the Ascension system.  We do this a bunch of times.
  int InternalInitializeBIRDSystem();

  // Description:
  // Close the Ascension system.  Useful if we have 
  // an error and want to quit in the middle of a function.
  int InternalCloseBIRDSystem();

  // Description:
  // Set the version information.
  // vtkSetStringMacro(Version);

  // Description:
  // Start the tracking system.  The tracking system is brought from
  // its ground state into full tracking mode.  The MICROBIRD will
  // only be reset if communication cannot be established without
  // a reset.
  int InternalStartTracking();

  // Description:
  // Stop the tracking system and bring it back to its ground state:
  // Initialized, not tracking, at 9600 Baud.
  int InternalStopTracking();

  // Description:
  // Methods for detecting which ports have tools in them, and
  // auto-enabling those tools.
  void EnableToolPorts();
  void DisableToolPorts();

  // Description:
  // Methods for enabling and disabling the transmitter.
  void EnableTransmitter();
  void DisableTransmitter();

  // use probe() to fill in the tracker default values.
  vtkAscension3DGConfig *m_TrackerCurrentConfig;
  
  vtkMatrix4x4 *SendMatrix;
  int IsTracking;

  int PortEnabled[VTK_3DG_NTOOLS];
  unsigned char *VirtualSROM[VTK_3DG_NTOOLS]; // is this needed?

  DOUBLE_ALL_TIME_STAMP_Q_RECORD record[VTK_3DG_NTOOLS];
  DOUBLE_ALL_TIME_STAMP_Q_RECORD *pRecord;

  char CommandReply[VTK_3DG_REPLY_LEN];

  // to simplify the start.
  bool m_bUseDefaultSystemSettings;
  bool m_bUseDefaultSensorSettings;

  // for changing the different data collection types.
  bool m_bUseSynchronous;  // if true use GetSynchronousRecord, otherwise use GetAsynchronousRecord
  bool m_bUseAllSensors;  // if true use ALL_SENSORS, otherwise loop through each sensor.

private:
  vtkAscension3DGTracker(const vtkAscension3DGTracker&);
  void operator=(const vtkAscension3DGTracker&);  
};

#endif


	#define HEMISPHERE_FRONT	1
	#define HEMISPHERE_BACK		2
	#define HEMISPHERE_TOP		3
	#define HEMISPHERE_BOTTOM	4
	#define HEMISPHERE_LEFT		5
	#define HEMISPHERE_RIGHT	6