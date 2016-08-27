# Generated by the VisualDSP++ IDDE

# Note:  Any changes made to this Makefile will be lost the next time the
# matching project file is loaded into the IDDE.  If you wish to preserve
# changes, rename this file and run it externally to the IDDE.

# The syntax of this Makefile is such that GNU Make v3.77 or higher is
# required.

# The current working directory should be the directory in which this
# Makefile resides.

# Supported targets:
#     sml3_Debug
#     sml3_Debug_clean

# Define this variable if you wish to run this Makefile on a host
# other than the host that created it and VisualDSP++ may be installed
# in a different directory.

ADI_DSP=C:\Program Files\Analog Devices\VisualDSP 5.0


# $VDSP is a gmake-friendly version of ADI_DIR

empty:=
space:= $(empty) $(empty)
VDSP_INTERMEDIATE=$(subst \,/,$(ADI_DSP))
VDSP=$(subst $(space),\$(space),$(VDSP_INTERMEDIATE))

RM=cmd /C del /F /Q

#
# Begin "sml3_Debug" configuration
#

ifeq ($(MAKECMDGOALS),sml3_Debug)

sml3_Debug : ../sml3.dlb 

Debug/L3_SDRAM.doj :L3_SDRAM.c L3_SDRAM.h ../system.h $(VDSP)/Blackfin/include/cdefBF561.h $(VDSP)/Blackfin/include/defBF561.h $(VDSP)/Blackfin/include/def_LPBlackfin.h $(VDSP)/Blackfin/include/cdef_LPBlackfin.h $(VDSP)/Blackfin/include/ccblkfn.h $(VDSP)/Blackfin/include/stdlib.h $(VDSP)/Blackfin/include/yvals.h $(VDSP)/Blackfin/include/stdlib_bf.h $(VDSP)/Blackfin/include/builtins.h $(VDSP)/Blackfin/include/sys/builtins_support.h $(VDSP)/Blackfin/include/fract_typedef.h $(VDSP)/Blackfin/include/fr2x16_typedef.h $(VDSP)/Blackfin/include/r2x16_typedef.h $(VDSP)/Blackfin/include/raw_typedef.h $(VDSP)/Blackfin/include/sys/anomaly_macros_rtl.h $(VDSP)/Blackfin/include/sys/mc_typedef.h $(VDSP)/Blackfin/include/sys/exception.h 
	@echo ".\L3_SDRAM.c"
	$(VDSP)/ccblkfn.exe -c .\L3_SDRAM.c -file-attr ProjectName=sml3 -O -Ov100 -g -structs-do-not-overlap -no-multiline -double-size-32 -decls-strong -warn-protos -mem -si-revision 0.3 -proc ADSP-BF561 -o .\Debug\L3_SDRAM.doj -MM

../sml3.dlb :./Debug/L3_SDRAM.doj 
	@echo "Creating library..."
	$(VDSP)/ccblkfn.exe -proc ADSP-BF561 -build-lib -o ..\sml3.dlb .\Debug\L3_SDRAM.doj -MM

endif

ifeq ($(MAKECMDGOALS),sml3_Debug_clean)

sml3_Debug_clean:
	-$(RM) "Debug\L3_SDRAM.doj"
	-$(RM) "..\sml3.dlb"
	-$(RM) ".\Debug\*.ipa"
	-$(RM) ".\Debug\*.opa"
	-$(RM) ".\Debug\*.ti"
	-$(RM) ".\Debug\*.pgi"
	-$(RM) ".\*.rbld"

endif


