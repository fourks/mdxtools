#ifndef VGM_H__
#define VGM_H__

#include "exceptionf.h"
#include "FileStream.h"
#include "wchar.h"

struct VGM {
	VGM() {}
	VGM(const char *filename) {
		load(filename);
	}
	~VGM() {}
	
	FileStream f;
	
	// These fields correspond to the file header
	uint32_t
		eof_offset, version, sn76489_clock,
		ym2413_clock, gd3_offset, total_samples, loop_offset,
		loop_samples, rate;
	uint16_t sn76489_feedback;
	uint8_t sn76489_shift_reg_width, sn76489_flags;
	uint32_t ym2612_clock,
		ym2151_clock, vgm_data_offset, sega_pcm_clock, sega_pcm_interface_reg,
		rf5c68_clock, ym2203_clock, ym2608_clock, ym2610b_clock,
		ym3812_clock, ym3526_clock, ym8950_clock, ymf262_clock,
		ymf278b_clock, ymf271_clock, ymz280b_clock, rf5c164_clock,
		pwm_clock, ay8910_clock;
	uint8_t ay8910_chip_type;
	uint32_t ay_flags; // only 3 bytes used
	uint8_t volume_modifier, loop_base, loop_modifier;
	uint32_t
		gb_dmg_clock, nes_apu_clock, multipcm_clock, upd7759_clock,
		okim6258_clock;
	uint8_t okim6258_flags, k051649_flags, c140_chip_type;
	uint32_t okim6295_clock, k051649_clock,
		k054539_clock, huc6280_clock, c140_clock, k053260_clock,
		pokey_clock, qsound_clock;
	uint32_t extra_header_offset;

	void load(const char *filename) {
		f.open(filename);
		if(!f.readCompare("Vgm ")) {
			throw new exceptionf("File header not \"Vgm \": %s", filename);
		}
		eof_offset = f.tell() + f.readUint32();
		version = f.readUint32();
		sn76489_clock = f.readUint32();
		ym2413_clock = f.readUint32();
		gd3_offset = f.tell() + f.readUint32();
		total_samples = f.readUint32();
		loop_offset = f.tell() + f.readUint32();
		loop_samples = f.readUint32();
		if(version >= 0x101) {
			rate = f.readUint32();
		} else {
			rate = 0;
		}
		if(version >= 0x110) {
			sn76489_feedback = f.readUint16();
			sn76489_shift_reg_width = f.readUint8();
		} else {
			sn76489_feedback = 0;
			sn76489_shift_reg_width = 0;
		}
		if(version >= 0x151) {
			sn76489_flags = f.readUint8();
		} else {
			f.readUint8(); // ignore a byte
			sn76489_flags = 0;
		}
		if(version >= 0x110) {
			ym2612_clock = f.readUint32();
			ym2151_clock = f.readUint32();
		} else {
			ym2612_clock = 0;
			ym2151_clock = 0;
		}
		if(version >= 0x150) {
			vgm_data_offset = f.tell() + f.readUint32();
		} else {
			vgm_data_offset = 0x40;
		}
		if(version >= 0x151) {
			sega_pcm_clock = f.readUint32();
			sega_pcm_interface_reg = f.readUint32();
			rf5c68_clock = f.readUint32();
			ym2203_clock = f.readUint32();
			ym2608_clock = f.readUint32();
			ym2610b_clock = f.readUint32();
			ym3812_clock = f.readUint32();
			ym3526_clock = f.readUint32();
			ym8950_clock = f.readUint32();
			ymf262_clock = f.readUint32();
			ymf278b_clock = f.readUint32();
			ymf271_clock = f.readUint32();
			ymz280b_clock = f.readUint32();
			rf5c164_clock = f.readUint32();
			pwm_clock = f.readUint32();
			ay8910_clock = f.readUint32();
			ay8910_chip_type = f.readUint8();
			ay_flags = f.readUint8() | (f.readUint8() << 8) | (f.readUint8() << 16);
		} else {
			sega_pcm_clock = sega_pcm_interface_reg = rf5c68_clock =
			ym2203_clock = ym2608_clock = ym2610b_clock = ym3812_clock =
			ym3526_clock = ym8950_clock = ymf262_clock = ymf278b_clock =
			ymf271_clock = ymz280b_clock = rf5c164_clock = pwm_clock =
			ay8910_clock = ay8910_chip_type = ay_flags = 0;
		}
		if(version >= 0x160) {
			volume_modifier = f.readUint8();
			f.readUint8();
			loop_base = f.readUint8();
		} else {
			volume_modifier = 0;
			loop_base = 0;
			f.readUint8(); f.readUint8(); f.readUint8();
		}
		if(version >= 0x151) {
			loop_modifier = f.readUint8();
		} else {
			loop_modifier = 0;
			f.readUint8();
		}
		if(version >= 0x161) {
			gb_dmg_clock = f.readUint32();
			nes_apu_clock = f.readUint32();
			multipcm_clock = f.readUint32();
			upd7759_clock = f.readUint32();
			okim6258_clock = f.readUint32();
			okim6258_flags = f.readUint8();
			k051649_flags = f.readUint8();
			c140_chip_type = f.readUint8();
			f.readUint8();
			okim6295_clock = f.readUint32();
			k051649_clock = f.readUint32();
			k054539_clock = f.readUint32();
			huc6280_clock = f.readUint32();
			c140_clock = f.readUint32();
			k053260_clock = f.readUint32();
			pokey_clock = f.readUint32();
			qsound_clock = f.readUint32();
		} else {
			loop_modifier = gb_dmg_clock = nes_apu_clock = multipcm_clock =
			upd7759_clock = okim6258_clock = okim6258_flags = k051649_flags =
			c140_chip_type = okim6295_clock = k051649_clock = k054539_clock =
			huc6280_clock = c140_clock = k053260_clock = pokey_clock = qsound_clock = 0;
		}
		if(Version >= 0x170) {
			extra_header_offset = f.readUint32();
		}

		printf("eof_offset=0x%08x (%d) version=0x%08x sn76489_clock=0x%08x ym2413_clock=0x%08x gd3_offset=0x%08x\n", eof_offset, eof_offset, version, sn76489_clock, ym2413_clock, gd3_offset);
		if(gd3_offset) loadGD3();

		f.seek(vgm_data_offset);
	}

	uint16_t *track_name_en, *track_name_jp;
	uint16_t *game_name_en, *game_name_jp;
	uint16_t *system_name_en, *system_name_jp;
	uint16_t *original_track_author_en, *original_track_author_jp;
	uint16_t *release_date, *converter;
	uint16_t *notes;

	bool loadGD3() {
		f.seek(gd3_offset);
		if(!f.readCompare("Gd3 ")) {
			printf("Not a GD3\n");
			return false;
		}
		uint32_t version = f.readUint32();
		uint32_t data_length = f.readUint32();
		printf("gd3 version 0x%08x data_length=0x%08x\n", version, data_length);
		uint16_t *data = new uint16_t[data_length];
		f.read(data, data_length);
		uint16_t *p = data;
		int n = 0;
		track_name_en = p;
		while(*p && n < data_length) { p++; n++; }; track_name_jp = p;
		while(*p && n < data_length) { p++; n++; }; game_name_en = p;
		while(*p && n < data_length) { p++; n++; }; game_name_jp = p;
		while(*p && n < data_length) { p++; n++; }; system_name_en = p;
		while(*p && n < data_length) { p++; n++; }; system_name_jp = p;
		while(*p && n < data_length) { p++; n++; }; original_track_author_en = p;
		while(*p && n < data_length) { p++; n++; }; original_track_author_jp = p;
		while(*p && n < data_length) { p++; n++; }; release_date = p;
		while(*p && n < data_length) { p++; n++; }; converter = p;
		while(*p && n < data_length) { p++; n++; }; notes = p;
	}

	void dumpInfo() {
		printf("VGM version %x\n", version);
		#define PRINTVAR(x) { printf("%s =\t0x%08x (%d)\n", #x, (x), (x)); }
		PRINTVAR(eof_offset);
		PRINTVAR(version);
		PRINTVAR(sn76489_clock);
		PRINTVAR(ym2413_clock);
		PRINTVAR(gd3_offset);
		PRINTVAR(total_samples);
		PRINTVAR(loop_offset);
		PRINTVAR(loop_samples);
		PRINTVAR(rate);
		PRINTVAR(sn76489_feedback);
		PRINTVAR(sn76489_shift_reg_width);
		PRINTVAR(sn76489_flags);
		PRINTVAR(ym2612_clock);
		PRINTVAR(ym2151_clock);
		PRINTVAR(vgm_data_offset);
		PRINTVAR(sega_pcm_clock);
		PRINTVAR(sega_pcm_interface_reg);
		PRINTVAR(rf5c68_clock);
		PRINTVAR(ym2203_clock);
		PRINTVAR(ym2608_clock);
		PRINTVAR(ym2610b_clock);
		PRINTVAR(ym3812_clock);
		PRINTVAR(ym3526_clock);
		PRINTVAR(ym8950_clock);
		PRINTVAR(ymf262_clock);
		PRINTVAR(ymf278b_clock);
		PRINTVAR(ymf271_clock);
		PRINTVAR(ymz280b_clock);
		PRINTVAR(rf5c164_clock);
		PRINTVAR(pwm_clock);
		PRINTVAR(ay8910_clock);
		PRINTVAR(ay8910_chip_type);
		PRINTVAR(ay_flags);
		PRINTVAR(volume_modifier);
		PRINTVAR(loop_base);
		PRINTVAR(loop_modifier);
		PRINTVAR(gb_dmg_clock);
		PRINTVAR(nes_apu_clock);
		PRINTVAR(multipcm_clock);
		PRINTVAR(upd7759_clock);
		PRINTVAR(okim6258_clock);
		PRINTVAR(okim6258_flags);
		PRINTVAR(k051649_flags);
		PRINTVAR(c140_chip_type);
		PRINTVAR(okim6295_clock);
		PRINTVAR(k051649_clock);
		PRINTVAR(k054539_clock);
		PRINTVAR(huc6280_clock);
		PRINTVAR(c140_clock);
		PRINTVAR(k053260_clock);
		PRINTVAR(pokey_clock);
		PRINTVAR(qsound_clock);
		PRINTVAR(extra_header_offset);
		#undef PRINTVAR

		wprintf(L"track_name_en: %s\n", track_name_en);
		wprintf(L"track_name_jp: %s\n", track_name_jp);
		wprintf(L"game_name_en: %s\n", game_name_en);
		wprintf(L"game_name_jp: %s\n", game_name_jp);
		wprintf(L"system_name_en: %s\n", system_name_en);
		wprintf(L"system_name_jp: %s\n", system_name_jp);
		wprintf(L"original_track_author_en: %s\n", original_track_author_en);
		wprintf(L"original_track_author_jp: %s\n", original_track_author_jp);
		wprintf(L"release_date: %s\n", release_date);
		wprintf(L"converter: %s\n", converter);
		wprintf(L"notes: %s\n", notes);
	}
};

#endif /* VGM_H__ */