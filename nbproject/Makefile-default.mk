#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/ATU100_PIC16F1938.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/ATU100_PIC16F1938.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=src/main.c src/oled_control.c src/pic_init.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/main.p1 ${OBJECTDIR}/src/oled_control.p1 ${OBJECTDIR}/src/pic_init.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/src/main.p1.d ${OBJECTDIR}/src/oled_control.p1.d ${OBJECTDIR}/src/pic_init.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/main.p1 ${OBJECTDIR}/src/oled_control.p1 ${OBJECTDIR}/src/pic_init.p1

# Source Files
SOURCEFILES=src/main.c src/oled_control.c src/pic_init.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/ATU100_PIC16F1938.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=16F1938
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/main.p1: src/main.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.p1.d 
	@${RM} ${OBJECTDIR}/src/main.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O1 -fasmfile -maddrqual=require -DDEFAULT -DCOMPILER_XC8 -UDEBUG -UNDEBUG -U__DOXYGEN__ -UCOMPILER_SDCC -xassembler-with-cpp -I"include" -v -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/src/main.p1 src/main.c 
	@-${MV} ${OBJECTDIR}/src/main.d ${OBJECTDIR}/src/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/oled_control.p1: src/oled_control.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/oled_control.p1.d 
	@${RM} ${OBJECTDIR}/src/oled_control.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O1 -fasmfile -maddrqual=require -DDEFAULT -DCOMPILER_XC8 -UDEBUG -UNDEBUG -U__DOXYGEN__ -UCOMPILER_SDCC -xassembler-with-cpp -I"include" -v -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/src/oled_control.p1 src/oled_control.c 
	@-${MV} ${OBJECTDIR}/src/oled_control.d ${OBJECTDIR}/src/oled_control.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/oled_control.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/pic_init.p1: src/pic_init.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/pic_init.p1.d 
	@${RM} ${OBJECTDIR}/src/pic_init.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O1 -fasmfile -maddrqual=require -DDEFAULT -DCOMPILER_XC8 -UDEBUG -UNDEBUG -U__DOXYGEN__ -UCOMPILER_SDCC -xassembler-with-cpp -I"include" -v -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/src/pic_init.p1 src/pic_init.c 
	@-${MV} ${OBJECTDIR}/src/pic_init.d ${OBJECTDIR}/src/pic_init.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/pic_init.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/src/main.p1: src/main.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.p1.d 
	@${RM} ${OBJECTDIR}/src/main.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O1 -fasmfile -maddrqual=require -DDEFAULT -DCOMPILER_XC8 -UDEBUG -UNDEBUG -U__DOXYGEN__ -UCOMPILER_SDCC -xassembler-with-cpp -I"include" -v -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/src/main.p1 src/main.c 
	@-${MV} ${OBJECTDIR}/src/main.d ${OBJECTDIR}/src/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/oled_control.p1: src/oled_control.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/oled_control.p1.d 
	@${RM} ${OBJECTDIR}/src/oled_control.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O1 -fasmfile -maddrqual=require -DDEFAULT -DCOMPILER_XC8 -UDEBUG -UNDEBUG -U__DOXYGEN__ -UCOMPILER_SDCC -xassembler-with-cpp -I"include" -v -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/src/oled_control.p1 src/oled_control.c 
	@-${MV} ${OBJECTDIR}/src/oled_control.d ${OBJECTDIR}/src/oled_control.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/oled_control.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/pic_init.p1: src/pic_init.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/pic_init.p1.d 
	@${RM} ${OBJECTDIR}/src/pic_init.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -O1 -fasmfile -maddrqual=require -DDEFAULT -DCOMPILER_XC8 -UDEBUG -UNDEBUG -U__DOXYGEN__ -UCOMPILER_SDCC -xassembler-with-cpp -I"include" -v -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,+hex,+file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto     -o ${OBJECTDIR}/src/pic_init.p1 src/pic_init.c 
	@-${MV} ${OBJECTDIR}/src/pic_init.d ${OBJECTDIR}/src/pic_init.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/pic_init.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: createResponseFiles
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
nbproject/$(CND_CONF).$(IMAGE_TYPE):   nbproject/Makefile-${CND_CONF}.mk    
		@cmd /C "gnuecho -n "-mcpu=$(MP_PROCESSOR_OPTION) $(MP_EXTRA_LD_PRE) -Wl,-Map=dist/${CND_CONF}/${IMAGE_TYPE}/ATU100_PIC16F1938.X.${IMAGE_TYPE}.map " > nbproject/default.debug"
	@cmd /C "gnuecho -n "-D__DEBUG=1 " >> nbproject/default.debug"
	@cmd /C "gnuecho -n "-fno-short-double -fno-short-float " >> nbproject/default.debug"
	@cmd /C "gnuecho -n "-O1 -fasmfile -maddrqual=require " >> nbproject/default.debug"
	@cmd /C "gnuecho -n "-DDEFAULT -DCOMPILER_XC8 -UDEBUG -UNDEBUG -U__DOXYGEN__ -UCOMPILER_SDCC -xassembler-with-cpp -I\"include\" -v -mwarn=-3 -Wa,-a " >> nbproject/default.debug"
	@cmd /C "gnuecho -n "-DXPRJ_default=$(CND_CONF) " >> nbproject/default.debug"
	@cmd /C "gnuecho -n "-mdfp=\"${DFP_DIR}/xc8\" " >> nbproject/default.debug"
	@cmd /C "gnuecho -n "-msummary=+psect,+class,+mem,+hex,+file " >> nbproject/default.debug"
	@cmd /C "gnuecho -n "-ginhx32 " >> nbproject/default.debug"
	@cmd /C "gnuecho -n "-Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall " >> nbproject/default.debug"
	@cmd /C "gnuecho -n "-std=c99 -gdwarf-3 -mstack=compiled:auto:auto " >> nbproject/default.debug"
	@cmd /C "gnuecho -n "-Wl,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml " >> nbproject/default.debug"
	@cmd /C "gnuecho -n "-o dist/${CND_CONF}/${IMAGE_TYPE}/ATU100_PIC16F1938.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} " >> nbproject/default.debug"
	@cmd /C "gnuecho -n "${OBJECTDIR}/src/main.p1 ${OBJECTDIR}/src/oled_control.p1 ${OBJECTDIR}/src/pic_init.p1 " >> nbproject/default.debug"

	
else
nbproject/$(CND_CONF).$(IMAGE_TYPE):   nbproject/Makefile-${CND_CONF}.mk   
		@cmd /C "gnuecho -n "-mcpu=$(MP_PROCESSOR_OPTION) $(MP_EXTRA_LD_PRE) -Wl,-Map=dist/${CND_CONF}/${IMAGE_TYPE}/ATU100_PIC16F1938.X.${IMAGE_TYPE}.map " > nbproject/default.production"
	@cmd /C "gnuecho -n "-fno-short-double -fno-short-float " >> nbproject/default.production"
	@cmd /C "gnuecho -n "-O1 -fasmfile -maddrqual=require " >> nbproject/default.production"
	@cmd /C "gnuecho -n "-DDEFAULT -DCOMPILER_XC8 -UDEBUG -UNDEBUG -U__DOXYGEN__ -UCOMPILER_SDCC -xassembler-with-cpp -I\"include\" -v -mwarn=-3 -Wa,-a " >> nbproject/default.production"
	@cmd /C "gnuecho -n "-DXPRJ_default=$(CND_CONF) " >> nbproject/default.production"
	@cmd /C "gnuecho -n "-mdfp=\"${DFP_DIR}/xc8\" " >> nbproject/default.production"
	@cmd /C "gnuecho -n "-msummary=+psect,+class,+mem,+hex,+file " >> nbproject/default.production"
	@cmd /C "gnuecho -n "-ginhx32 " >> nbproject/default.production"
	@cmd /C "gnuecho -n "-Wl,--data-init -mno-keep-startup -mno-osccal -mno-resetbits -mno-save-resetbits -mno-download -mno-stackcall " >> nbproject/default.production"
	@cmd /C "gnuecho -n "-std=c99 -gdwarf-3 -mstack=compiled:auto:auto " >> nbproject/default.production"
	@cmd /C "gnuecho -n "-Wl,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml " >> nbproject/default.production"
	@cmd /C "gnuecho -n "-o dist/${CND_CONF}/${IMAGE_TYPE}/ATU100_PIC16F1938.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} " >> nbproject/default.production"
	@cmd /C "gnuecho -n "${OBJECTDIR}/src/main.p1 ${OBJECTDIR}/src/oled_control.p1 ${OBJECTDIR}/src/pic_init.p1 " >> nbproject/default.production"

	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: linkWithResponseFileStandalone
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/ATU100_PIC16F1938.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES} nbproject/$(CND_CONF).$(IMAGE_TYPE)  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC}  @nbproject/$(CND_CONF).$(IMAGE_TYPE) 
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/ATU100_PIC16F1938.X.${IMAGE_TYPE}.hex 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/ATU100_PIC16F1938.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES} nbproject/$(CND_CONF).$(IMAGE_TYPE)  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC}  @nbproject/$(CND_CONF).$(IMAGE_TYPE) 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
