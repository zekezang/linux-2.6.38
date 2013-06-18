/*
 * linux/arch/arm/mach-s3c64xx/mini6410-lcds.c
 *
 * Copyright (c) 2012 FriendlyARM (www.arm9.net)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/string.h>

#include <plat/ctouch.h>

#if defined(CONFIG_FB_S3C_EXT_MINI6410)
#include <mach/s3cfb.h>

/*
 * s3cfb configs for supported LCD
 *
 * NOTE:
 * 1) freq used as CLKVAL of S3C6410 VIDCON0, and
 * 2) CLKVAL is defined upon 133 MHz HCLK, pls update it when HCLK changed
 * 3) so, VCLK = 133 MHz / (freq + 1)
 */

static struct s3cfb_lcd hvga_n43 = {
	.width = 480,
	.height = 272,
	.p_width = 96,
	.p_height = 54,
	.bpp = 32,
	.freq = 11,

	.timing = {
		.h_fp =  4,
		.h_bp = 45,
		.h_sw =  6,
		.v_fp =  2,
		.v_fpe = 1,
		.v_bp =  3,
		.v_bpe = 1,
		.v_sw =  2,
	},
	.polarity = {
		.rise_vclk = 1,
		.inv_hsync = 0,
		.inv_vsync = 0,
		.inv_vden = 0,
	},
};

static struct s3cfb_lcd hvga_h43 = {
	.width = 480,
	.height = 272,
	.p_width = 96,
	.p_height = 54,
	.bpp = 32,
	.freq = 13,

	.timing = {
		.h_fp =  5,
		.h_bp = 40,
		.h_sw =  2,
		.v_fp =  8,
		.v_fpe = 1,
		.v_bp =  8,
		.v_bpe = 1,
		.v_sw =  2,
	},
	.polarity = {
		.rise_vclk = 0,
		.inv_hsync = 1,
		.inv_vsync = 1,
		.inv_vden = 0,
	},
};

static struct s3cfb_lcd wvga_a70 = {
	.width = 800,
	.height = 480,
	.p_width = 152,
	.p_height = 90,
	.bpp = 32,
	.freq = 3,

	.timing = {
		.h_fp = 40,
		.h_bp = 40,
		.h_sw = 48,
		.v_fp = 17,
		.v_fpe = 1,
		.v_bp = 29,
		.v_bpe = 1,
		.v_sw = 24,
	},
	.polarity = {
		.rise_vclk = 0,
		.inv_hsync = 1,
		.inv_vsync = 1,
		.inv_vden = 0,
	},
};

static struct s3cfb_lcd wvga_s70 = {
	.width = 800,
	.height = 480,
	.p_width = 154,
	.p_height = 96,
	.bpp = 32,
	.freq = 3,

	.timing = {
		.h_fp = 80,
		.h_bp = 36,
		.h_sw = 10,
		.v_fp = 22,
		.v_fpe = 1,
		.v_bp = 15,
		.v_bpe = 1,
		.v_sw = 8,
	},
	.polarity = {
		.rise_vclk = 0,
		.inv_hsync = 1,
		.inv_vsync = 1,
		.inv_vden = 0,
	},
};

static struct s3cfb_lcd wvga_w50 = {
	.width = 800,
	.height = 480,
	.p_width = 108,
	.p_height = 64,
	.bpp = 32,
	.freq = 3,

	.timing = {
		.h_fp = 40,
		.h_bp = 40,
		.h_sw = 48,
		.v_fp = 20,
		.v_fpe = 1,
		.v_bp = 20,
		.v_bpe = 1,
		.v_sw = 12,
	},
	.polarity = {
		.rise_vclk = 0,
		.inv_hsync = 1,
		.inv_vsync = 1,
		.inv_vden = 0,
	},
};

static struct s3cfb_lcd wsvga_w101 = {
	.width = 1024,
	.height = 600,
	.p_width = 204,
	.p_height = 120,
	.bpp = 32,
	.freq = 2,

	.timing = {
		.h_fp = 40,
		.h_bp = 40,
		.h_sw = 110,
		.v_fp =  6,
		.v_fpe = 1,
		.v_bp =  6,
		.v_bpe = 1,
		.v_sw =  6,
	},
	.polarity = {
		.rise_vclk = 0,
		.inv_hsync = 1,
		.inv_vsync = 1,
		.inv_vden = 0,
	},
};

static struct s3cfb_lcd qvga_t35 = {
	.width = 240,
	.height = 320,
	.p_width = 52,
	.p_height = 70,
	.bpp = 32,
	.freq = 11,

	.timing = {
		.h_fp =  4,
		.h_bp =  1,
		.h_sw = 30,
		.v_fp =  1,
		.v_fpe = 1,
		.v_bp =  1,
		.v_bpe = 1,
		.v_sw =  4,
	},
	.polarity = {
		.rise_vclk = 0,
		.inv_hsync = 1,
		.inv_vsync = 1,
		.inv_vden = 0,
	},
};

static struct s3cfb_lcd qvga_x35 = {
	.width = 240,
	.height = 320,
	.p_width = 52,
	.p_height = 70,
	.bpp = 32,
	.freq = 23,

	.timing = {
		.h_fp =  6,
		.h_bp =  8,
		.h_sw = 18,
		.v_fp =  2,
		.v_fpe = 1,
		.v_bp =  4,
		.v_bpe = 1,
		.v_sw = 10,
	},
	.polarity = {
		.rise_vclk = 1,
		.inv_hsync = 0,
		.inv_vsync = 0,
		.inv_vden = 1,
	},
};

static struct s3cfb_lcd qvga_zq35 = {
	.width = 320,
	.height = 240,
	.p_width = 70,
	.p_height = 52,
	.bpp = 32,
	.freq = 22,

	.timing = {
		.h_fp =  4,
		.h_bp = 70,
		.h_sw =  1,
		.v_fp =  4,
		.v_fpe = 1,
		.v_bp = 12,
		.v_bpe = 1,
		.v_sw =  1,
	},
	.polarity = {
		.rise_vclk = 0,
		.inv_hsync = 1,
		.inv_vsync = 1,
		.inv_vden = 0,
	},
};

/* VGAs */
static struct s3cfb_lcd vga_g10 = {
	.width = 640,
	.height = 480,
	.p_width = 213,
	.p_height = 160,
	.bpp = 32,
	.freq = 4,

	.timing = {
		.h_fp = 0x3c,
		.h_bp = 0x63,
		.h_sw = 1,
		.v_fp = 0x0a,
		.v_fpe = 1,
		.v_bp = 0x22,
		.v_bpe = 1,
		.v_sw = 1,
	},
	.polarity = {
		.rise_vclk = 0,
		.inv_hsync = 0,
		.inv_vsync = 0,
		.inv_vden = 0,
	},
};

static struct s3cfb_lcd vga_l80 = {
	.width = 640,
	.height = 480,
	.p_width = 160,
	.p_height = 120,
	.bpp = 32,
	.freq = 3,

	.timing = {
		.h_fp = 3,
		.h_bp = 3,
		.h_sw = 0x28,
		.v_fp = 1,
		.v_fpe = 1,
		.v_bp = 1,
		.v_bpe = 1,
		.v_sw = 1,
	},
	.polarity = {
		.rise_vclk = 0,
		.inv_hsync = 0,
		.inv_vsync = 0,
		.inv_vden = 0,
	},
};

static struct s3cfb_lcd xga = {
	.width = 1024,
	.height = 768,
	.p_width = 160,
	.p_height = 120,
	.bpp = 32,
	.freq = 5,

	.timing = {
		.h_fp = 2,
		.h_bp = 2,
		.h_sw = 0x2a,
		.v_fp = 2,
		.v_fpe = 1,
		.v_bp = 2,
		.v_bpe = 1,
		.v_sw = 0x10,
	},
	.polarity = {
		.rise_vclk = 0,
		.inv_hsync = 0,
		.inv_vsync = 0,
		.inv_vden = 0,
	},
};

static struct s3cfb_lcd svga = {
	.width = 800,
	.height = 600,
	.p_width = 160,
	.p_height = 120,
	.bpp = 32,
	.freq = 5,

	.timing = {
		.h_fp = 2,
		.h_bp = 2,
		.h_sw = 0x2a,
		.v_fp = 2,
		.v_fpe = 1,
		.v_bp = 2,
		.v_bpe = 1,
		.v_sw = 0x10,
	},
	.polarity = {
		.rise_vclk = 0,
		.inv_hsync = 0,
		.inv_vsync = 0,
		.inv_vden = 0,
	},
};

static struct s3cfb_lcd vga = {
	.width = 640,
	.height = 480,
	.p_width = 160,
	.p_height = 120,
	.bpp = 32,
	.freq = 5,

	.timing = {
		.h_fp = 2,
		.h_bp = 2,
		.h_sw = 0x2a,
		.v_fp = 2,
		.v_fpe = 1,
		.v_bp = 2,
		.v_bpe = 1,
		.v_sw = 0x10,
	},
	.polarity = {
		.rise_vclk = 0,
		.inv_hsync = 0,
		.inv_vsync = 0,
		.inv_vden = 0,
	},
};

static struct s3cfb_lcd ezvga = {
	.width = 800,
	.height = 600,
	.p_width = 160,
	.p_height = 120,
	.bpp = 32,
	.freq = 2,

	.timing = {
		.h_fp = 0x11,
		.h_bp = 0xa8,
		.h_sw = 0x2a,
		.v_fp = 2,
		.v_fpe = 1,
		.v_bp = 2,
		.v_bpe = 1,
		.v_sw = 0x10,
	},
	.polarity = {
		.rise_vclk = 0,
		.inv_hsync = 0,
		.inv_vsync = 0,
		.inv_vden = 0,
	},
};


/* Try to guess LCD panel by kernel command line, or
 * using *H43* as default */

static struct {
	char *name;
	struct s3cfb_lcd *lcd;
	int ctp;
	int has_ts;
} mini210_lcd_config[] = {
	{ "H43",		&hvga_h43,		1, 1 },
	{ "N43",		&hvga_n43,		0, 1 },
	{ "T35",		&qvga_t35,		0, 1 },
	{ "X35",		&qvga_x35,		0, 1 },
	{ "W35",		&qvga_zq35,		0, 1 },
	{ "S70",		&wvga_s70,		1, 1 },
	{ "A70",		&wvga_a70,		0, 1 },
	{ "W50",		&wvga_w50,		0, 1 },
	{ "W101",		&wsvga_w101,	0, 1 },
	{ "G10",		&vga_g10,		0, 1 },
	{ "L80",		&vga_l80,		0, 1 },

	/* VGAs without TS */
	{ "VGA1024X768",&xga,			0, 0 },
	{ "VGA800X600",	&svga,			0, 0 },
	{ "VGA640X480",	&vga,			0, 0 },
	{ "EZVGA800X600",	&ezvga,		0, 0 },
};

static int lcd_idx = 0;

static int __init mini210_setup_lcd(char *str)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(mini210_lcd_config); i++) {
		if (!strcasecmp(mini210_lcd_config[i].name, str)) {
			lcd_idx = i;
			break;
		}
	}

	printk("MINI6410: %s selected\n", mini210_lcd_config[lcd_idx].name);
	return 0;
}
early_param("lcd", mini210_setup_lcd);


struct s3cfb_lcd *mini210_get_lcd(void)
{
	return mini210_lcd_config[lcd_idx].lcd;
}

void mini210_get_lcd_res(int *w, int *h)
{
	struct s3cfb_lcd *lcd = mini210_lcd_config[lcd_idx].lcd;

	if (w)
		*w = lcd->width;
	if (h)
		*h = lcd->height;

	return;
}
EXPORT_SYMBOL(mini210_get_lcd_res);

#endif /* CONFIG_FB_S3C_EXT_MINI6410 */


/* Capacity Touch Panel */
static unsigned int ctp_type = CTP_NONE;

static int __init mini210_set_ctp(char *str)
{
	unsigned int val;
	char *p = str, *end;

	val = simple_strtoul(p, &end, 10);
	if (end <= p) {
		return 1;
	}

#if defined(CONFIG_FB_S3C_EXT_MINI6410)
	if (val < CTP_MAX && mini210_lcd_config[lcd_idx].ctp) {
		ctp_type = val;
	}
#else
	if (val < CTP_MAX) {
		ctp_type = val;
	}
#endif

	return 1;
}
__setup("ctp=", mini210_set_ctp);

unsigned int mini210_get_ctp(void)
{
	return ctp_type;
}
EXPORT_SYMBOL(mini210_get_ctp);

