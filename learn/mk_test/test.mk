################################################################################
# Toolchains
################################################################################
ROOT				?= $(CURDIR)/..
TOOLCHAIN_ROOT 			?= $(ROOT)/toolchains


LOCAL_PATH:= $(call my-dir) 


include $(CLEAR_VARS)  
$(warning "the value of LOCAL_PATH is$(LOCAL_PATH)")

define runtest
	echo "yang test V0.0.0"
	echo "para0=$(0)"
	echo "para1=$(1)"
	echo "para2=$(2)"
	echo "para3=$(3)"
endef


.PHONY: obj
obj:
	$(call runtest,$(ROOT),$(TOOLCHAIN_ROOT))
