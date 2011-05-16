//###########################################################################
// This file is part of LImA, a Library for Image Acquisition
//
// Copyright (C) : 2009-2011
// European Synchrotron Radiation Facility
// BP 220, Grenoble 38043
// FRANCE
//
// This is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// This software is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//###########################################################################
#ifndef SIMUHWINTERFACE_H
#define SIMUHWINTERFACE_H

#include "SimuCompatibility.h"
#include "HwInterface.h"
#include "Simulator.h"

namespace lima
{

class SimuHwInterface;

/*******************************************************************
 * \class SimuDetInfoCtrlObj
 * \brief Control object providing simulator detector info interface
 *******************************************************************/

class LIBSIMULATOR_API SimuDetInfoCtrlObj : public HwDetInfoCtrlObj
{
 public:
	SimuDetInfoCtrlObj(Simulator& simu);
	virtual ~SimuDetInfoCtrlObj();

	virtual void getMaxImageSize(Size& max_image_size);
	virtual void getDetectorImageSize(Size& det_image_size);

	virtual void getDefImageType(ImageType& def_image_type);
	virtual void getCurrImageType(ImageType& curr_image_type);
	virtual void setCurrImageType(ImageType  curr_image_type);

	virtual void getPixelSize(double& pixel_size);
	virtual void getDetectorType(std::string& det_type);
	virtual void getDetectorModel(std::string& det_model);

	virtual void registerMaxImageSizeCallback(
					HwMaxImageSizeCallback& cb);
	virtual void unregisterMaxImageSizeCallback(
					HwMaxImageSizeCallback& cb);

 private:
	class MaxImageSizeCallbackGen: public HwMaxImageSizeCallbackGen
	{
	protected:
		virtual void setMaxImageSizeCallbackActive(bool cb_active);
	};

	Simulator& m_simu;
	MaxImageSizeCallbackGen m_mis_cb_gen;
};


/*******************************************************************
 * \class SimuBufferCtrlObj
 * \brief Control object providing simulator buffering interface
 *******************************************************************/

class LIBSIMULATOR_API SimuBufferCtrlObj : public HwBufferCtrlObj
{
 public:
	SimuBufferCtrlObj(Simulator& simu);
	virtual ~SimuBufferCtrlObj();

	virtual void setFrameDim(const FrameDim& frame_dim);
	virtual void getFrameDim(      FrameDim& frame_dim);

	virtual void setNbBuffers(int  nb_buffers);
	virtual void getNbBuffers(int& nb_buffers);

	virtual void setNbConcatFrames(int  nb_concat_frames);
	virtual void getNbConcatFrames(int& nb_concat_frames);

	virtual void getMaxNbBuffers(int& max_nb_buffers);

	virtual void *getBufferPtr(int buffer_nb, int concat_frame_nb = 0);
	virtual void *getFramePtr(int acq_frame_nb);

	virtual void getStartTimestamp(Timestamp& start_ts);
	virtual void getFrameInfo(int acq_frame_nb, HwFrameInfoType& info);

	virtual void   registerFrameCallback(HwFrameCallback& frame_cb);
	virtual void unregisterFrameCallback(HwFrameCallback& frame_cb);

 private:
	Simulator& m_simu;
	BufferCtrlMgr& m_buffer_mgr;
};


/*******************************************************************
 * \class SimuSyncCtrlObj
 * \brief Control object providing simulator synchronization interface
 *******************************************************************/

class LIBSIMULATOR_API SimuSyncCtrlObj : public HwSyncCtrlObj
{
 public:
	SimuSyncCtrlObj(Simulator& simu);
	virtual ~SimuSyncCtrlObj();

	virtual bool checkTrigMode(TrigMode trig_mode);
	virtual void setTrigMode(TrigMode  trig_mode);
	virtual void getTrigMode(TrigMode& trig_mode);

	virtual void setExpTime(double  exp_time);
	virtual void getExpTime(double& exp_time);

	virtual void setLatTime(double  lat_time);
	virtual void getLatTime(double& lat_time);

	virtual void setNbHwFrames(int  nb_frames);
	virtual void getNbHwFrames(int& nb_frames);

	virtual void getValidRanges(ValidRangesType& valid_ranges);

 private:
	Simulator& m_simu;
};


/*******************************************************************
 * \class SimuBinCtrlObj
 * \brief Control object providing simulator binning interface
 *******************************************************************/

class LIBSIMULATOR_API SimuBinCtrlObj : public HwBinCtrlObj
{
 public:
	SimuBinCtrlObj(Simulator& simu);
	virtual ~SimuBinCtrlObj();

	virtual void setBin(const Bin& bin);
	virtual void getBin(Bin& bin);
	virtual void checkBin(Bin& bin);

 private:
	Simulator& m_simu;
};


/*******************************************************************
 * \class SimuHwInterface
 * \brief Simulator hardware interface
 *******************************************************************/

class LIBSIMULATOR_API SimuHwInterface : public HwInterface
{
 public:
	SimuHwInterface(Simulator& simu);
	virtual ~SimuHwInterface();

	virtual void getCapList(CapList&) const;

	virtual void reset(ResetLevel reset_level);
	virtual void prepareAcq();
	virtual void startAcq();
	virtual void stopAcq();
	virtual void getStatus(StatusType& status);
	virtual int getNbHwAcquiredFrames();

 private:
	Simulator& m_simu;
	CapList m_cap_list;
	SimuDetInfoCtrlObj m_det_info;
	SimuBufferCtrlObj  m_buffer;
	SimuSyncCtrlObj    m_sync;
	SimuBinCtrlObj     m_bin;
};

}

#endif // SIMUHWINTERFACE_H
