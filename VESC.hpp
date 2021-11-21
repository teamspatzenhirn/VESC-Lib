/**
 * @file VESC.hpp
 * @author Jonas Merkle [JJM] (jonas@jjm.one)
 * @date 10.06.21
 */

#ifndef CAROLO_APP_VESC_VESC_HPP
#define CAROLO_APP_VESC_VESC_HPP

#include <cstdint>

#include "./types/datatypes.h"
#include "VESCMaster.hpp"

/**
 * @namepsace VESCLib
 *
 * Namespace for all vesc related things.
 */
namespace VESCLib {

    /**
     * @class VESC
     *
     * This class provides an object which represents one of the connected vescs.
     */
    class VESC {

    public:

        /**
         * Initializes a new vesc object.
         * @param vescMaster A reference to the VescMaster object.
         * @param canID The can bus id of the vesc.
         */
        VESC(const VESCMaster *vescMaster, uint8_t canID);

        /**
         * Set the rpm of the vesc.
         * @param rpm The rpm to be set.
         *
         * CAUTION:
         * The rpm value represents a virtual rpm value. The real world motor rpm can be calculated by:
         * <realRpm> = <rpm>/<motorPolePairs>
         */
        void setRPM(int32_t rpm);

        /**
         * @brief Get performance information from the vesc.
         * 
         * @param [out] perfInfo Ptr to the performance information
         */
        void getPerfInfo(mc_values *perfInfo);


    private:

        /**
         * The reference to the vesc master object.
         */
        const VESCMaster *vescMaster;

        /**
         * The can bus id of the vesc
         */
        const uint8_t canID;

    };

}

#endif //CAROLO_APP_VESC_VESC_HPP
