#
# Makefile
#
CC = arm-linux-gcc
LVGL_DIR_NAME ?= lvgl
LVGL_DIR ?= ${shell pwd}
CFLAGS ?= -O3 -g0 -I$(LVGL_DIR)/ -I$(LVGL_DIR)/usrCode/inc -I/home/gec/tools/include/freetype2  -Wall -Wshadow -Wundef -Wmissing-prototypes -Wno-discarded-qualifiers -Wall -Wextra -Wno-unused-function -Wno-error=strict-prototypes -Wpointer-arith -fno-strict-aliasing -Wno-error=cpp -Wuninitialized -Wmaybe-uninitialized -Wno-unused-parameter -Wno-missing-field-initializers -Wtype-limits -Wsizeof-pointer-memaccess -Wno-format-nonliteral -Wno-cast-qual -Wunreachable-code -Wno-switch-default -Wreturn-type -Wmultichar -Wformat-security -Wno-ignored-qualifiers -Wno-error=pedantic -Wno-sign-compare -Wno-error=missing-prototypes -Wdouble-promotion -Wclobbered -Wdeprecated -Wempty-body -Wtype-limits -Wstack-usage=2048 -Wno-unused-value -Wno-unused-parameter -Wno-missing-field-initializers -Wuninitialized -Wmaybe-uninitialized -Wall -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wtype-limits -Wsizeof-pointer-memaccess -Wno-format-nonliteral -Wpointer-arith -Wno-cast-qual -Wmissing-prototypes -Wunreachable-code -Wno-switch-default -Wreturn-type -Wmultichar -Wno-discarded-qualifiers -Wformat-security -Wno-ignored-qualifiers -Wno-sign-compare -std=c99

LDFLAGS += -lm  -L/home/gec/tools/lib -lfreetype
BIN = demo

# 创建build目录
USRCODE_BUILD_DIR = $(LVGL_DIR)/usrCode/build

#Collect the files to compile
MAINSRC = ./main.c lv_font_source_han_sans_bold_20.c chinese_ziku.c

# 查找源文件
# usrcode下的普通.c文件（排除ui.c和img目录）
USRCODE_SRC = ${shell find $(LVGL_DIR)/usrCode -maxdepth 1 -name '*.c' -not -name 'ui.c'}
# usrcode/img下的图片相关.c文件
IMG_SRC = ${shell find $(LVGL_DIR)/usrCode/img -name '*.c'}
# ui.c文件单独指定
UI_SRC = $(LVGL_DIR)/usrCode/ui.c

# 合并所有用户代码源文件
USRCODESRC = $(USRCODE_SRC) $(IMG_SRC) $(UI_SRC)

include $(LVGL_DIR)/lvgl/lvgl.mk
include $(LVGL_DIR)/lv_drivers/lv_drivers.mk

CSRCS +=$(LVGL_DIR)/mouse_cursor_icon.c 

OBJEXT ?= .o

AOBJS = $(ASRCS:.S=$(OBJEXT))
COBJS = $(CSRCS:.c=$(OBJEXT))

MAINOBJ = $(MAINSRC:.c=$(OBJEXT))

# 为usrcode下的.o文件指定build目录路径 - 修复路径问题
USRCODEOBJ = $(USRCODE_SRC:$(LVGL_DIR)/usrCode/%.c=$(USRCODE_BUILD_DIR)/%.o) \
             $(IMG_SRC:$(LVGL_DIR)/usrCode/%.c=$(USRCODE_BUILD_DIR)/%.o) \
             $(UI_SRC:$(LVGL_DIR)/usrCode/%.c=$(USRCODE_BUILD_DIR)/%.o)

SRCS = $(ASRCS) $(CSRCS) $(MAINSRC) $(USRCODESRC)
OBJS = $(AOBJS) $(COBJS)

## MAINOBJ -> OBJFILES

all: default

# 确保build目录和子目录存在
$(USRCODE_BUILD_DIR):
	@mkdir -p $@
	@mkdir -p $(USRCODE_BUILD_DIR)/img

# 编译usrcode根目录下的.c文件
$(USRCODE_BUILD_DIR)/%.o: $(LVGL_DIR)/usrCode/%.c | $(USRCODE_BUILD_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "CC $< -> $@"

# 编译usrcode/img目录下的.c文件  
$(USRCODE_BUILD_DIR)/img/%.o: $(LVGL_DIR)/usrCode/img/%.c | $(USRCODE_BUILD_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "CC $< -> $@"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "CC $<"
    
default: $(AOBJS) $(COBJS) $(MAINOBJ) $(USRCODEOBJ)
	$(CC) -o $(BIN) $(MAINOBJ) $(AOBJS) $(COBJS) $(USRCODEOBJ) $(LDFLAGS)

clean: 
	rm -f $(BIN) $(AOBJS) $(COBJS) $(MAINOBJ)
	rm -rf $(USRCODE_BUILD_DIR)

.PHONY: all default clean