/* Determine the current selected locale.
   Copyright (C) 1995-1999, 2000-2004 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU Library General Public License as published
   by the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,
   USA.  */

/* Written by Ulrich Drepper <drepper@gnu.org>, 1995.  */
/* Win32 code written by Tor Lillqvist <tml@iki.fi>.  */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <stdlib.h>
#include <locale.h>

#if defined _WIN32 || defined __WIN32__
# undef WIN32   
# define WIN32
#endif

#ifdef WIN32
# define WIN32_LEAN_AND_MEAN
# include <windows.h>
# ifndef LANG_AFRIKAANS
# define LANG_AFRIKAANS 0x36
# endif
# ifndef LANG_ALBANIAN
# define LANG_ALBANIAN 0x1c
# endif
# ifndef LANG_AMHARIC
# define LANG_AMHARIC 0x5e
# endif
# ifndef LANG_ARABIC
# define LANG_ARABIC 0x01
# endif
# ifndef LANG_ARMENIAN
# define LANG_ARMENIAN 0x2b
# endif
# ifndef LANG_ASSAMESE
# define LANG_ASSAMESE 0x4d
# endif
# ifndef LANG_AZERI
# define LANG_AZERI 0x2c
# endif
# ifndef LANG_BASQUE
# define LANG_BASQUE 0x2d
# endif
# ifndef LANG_BELARUSIAN
# define LANG_BELARUSIAN 0x23
# endif
# ifndef LANG_BENGALI
# define LANG_BENGALI 0x45
# endif
# ifndef LANG_BURMESE
# define LANG_BURMESE 0x55
# endif
# ifndef LANG_CAMBODIAN
# define LANG_CAMBODIAN 0x53
# endif
# ifndef LANG_CATALAN
# define LANG_CATALAN 0x03
# endif
# ifndef LANG_CHEROKEE
# define LANG_CHEROKEE 0x5c
# endif
# ifndef LANG_DIVEHI
# define LANG_DIVEHI 0x65
# endif
# ifndef LANG_EDO
# define LANG_EDO 0x66
# endif
# ifndef LANG_ESTONIAN
# define LANG_ESTONIAN 0x25
# endif
# ifndef LANG_FAEROESE
# define LANG_FAEROESE 0x38
# endif
# ifndef LANG_FARSI
# define LANG_FARSI 0x29
# endif
# ifndef LANG_FRISIAN
# define LANG_FRISIAN 0x62
# endif
# ifndef LANG_FULFULDE
# define LANG_FULFULDE 0x67
# endif
# ifndef LANG_GAELIC
# define LANG_GAELIC 0x3c
# endif
# ifndef LANG_GALICIAN
# define LANG_GALICIAN 0x56
# endif
# ifndef LANG_GEORGIAN
# define LANG_GEORGIAN 0x37
# endif
# ifndef LANG_GUARANI
# define LANG_GUARANI 0x74
# endif
# ifndef LANG_GUJARATI
# define LANG_GUJARATI 0x47
# endif
# ifndef LANG_HAUSA
# define LANG_HAUSA 0x68
# endif
# ifndef LANG_HAWAIIAN
# define LANG_HAWAIIAN 0x75
# endif
# ifndef LANG_HEBREW
# define LANG_HEBREW 0x0d
# endif
# ifndef LANG_HINDI
# define LANG_HINDI 0x39
# endif
# ifndef LANG_IBIBIO
# define LANG_IBIBIO 0x69
# endif
# ifndef LANG_IGBO
# define LANG_IGBO 0x70
# endif
# ifndef LANG_INDONESIAN
# define LANG_INDONESIAN 0x21
# endif
# ifndef LANG_INUKTITUT
# define LANG_INUKTITUT 0x5d
# endif
# ifndef LANG_KANNADA
# define LANG_KANNADA 0x4b
# endif
# ifndef LANG_KANURI
# define LANG_KANURI 0x71
# endif
# ifndef LANG_KASHMIRI
# define LANG_KASHMIRI 0x60
# endif
# ifndef LANG_KAZAK
# define LANG_KAZAK 0x3f
# endif
# ifndef LANG_KONKANI
# define LANG_KONKANI 0x57
# endif
# ifndef LANG_KYRGYZ
# define LANG_KYRGYZ 0x40
# endif
# ifndef LANG_LAO
# define LANG_LAO 0x54
# endif
# ifndef LANG_LATIN
# define LANG_LATIN 0x76
# endif
# ifndef LANG_LATVIAN
# define LANG_LATVIAN 0x26
# endif
# ifndef LANG_LITHUANIAN
# define LANG_LITHUANIAN 0x27
# endif
# ifndef LANG_MACEDONIAN
# define LANG_MACEDONIAN 0x2f
# endif
# ifndef LANG_MALAY
# define LANG_MALAY 0x3e
# endif
# ifndef LANG_MALAYALAM
# define LANG_MALAYALAM 0x4c
# endif
# ifndef LANG_MALTESE
# define LANG_MALTESE 0x3a
# endif
# ifndef LANG_MANIPURI
# define LANG_MANIPURI 0x58
# endif
# ifndef LANG_MARATHI
# define LANG_MARATHI 0x4e
# endif
# ifndef LANG_MONGOLIAN
# define LANG_MONGOLIAN 0x50
# endif
# ifndef LANG_NEPALI
# define LANG_NEPALI 0x61
# endif
# ifndef LANG_ORIYA
# define LANG_ORIYA 0x48
# endif
# ifndef LANG_OROMO
# define LANG_OROMO 0x72
# endif
# ifndef LANG_PAPIAMENTU
# define LANG_PAPIAMENTU 0x79
# endif
# ifndef LANG_PASHTO
# define LANG_PASHTO 0x63
# endif
# ifndef LANG_PUNJABI
# define LANG_PUNJABI 0x46
# endif
# ifndef LANG_RHAETO_ROMANCE
# define LANG_RHAETO_ROMANCE 0x17
# endif
# ifndef LANG_SAAMI
# define LANG_SAAMI 0x3b
# endif
# ifndef LANG_SANSKRIT
# define LANG_SANSKRIT 0x4f
# endif
# ifndef LANG_SERBIAN
# define LANG_SERBIAN 0x1a
# endif
# ifndef LANG_SINDHI
# define LANG_SINDHI 0x59
# endif
# ifndef LANG_SINHALESE
# define LANG_SINHALESE 0x5b
# endif
# ifndef LANG_SLOVAK
# define LANG_SLOVAK 0x1b
# endif
# ifndef LANG_SOMALI
# define LANG_SOMALI 0x77
# endif
# ifndef LANG_SORBIAN
# define LANG_SORBIAN 0x2e
# endif
# ifndef LANG_SUTU
# define LANG_SUTU 0x30
# endif
# ifndef LANG_SWAHILI
# define LANG_SWAHILI 0x41
# endif
# ifndef LANG_SYRIAC
# define LANG_SYRIAC 0x5a
# endif
# ifndef LANG_TAGALOG
# define LANG_TAGALOG 0x64
# endif
# ifndef LANG_TAJIK
# define LANG_TAJIK 0x28
# endif
# ifndef LANG_TAMAZIGHT
# define LANG_TAMAZIGHT 0x5f
# endif
# ifndef LANG_TAMIL
# define LANG_TAMIL 0x49
# endif
# ifndef LANG_TATAR
# define LANG_TATAR 0x44
# endif
# ifndef LANG_TELUGU
# define LANG_TELUGU 0x4a
# endif
# ifndef LANG_THAI
# define LANG_THAI 0x1e
# endif
# ifndef LANG_TIBETAN
# define LANG_TIBETAN 0x51
# endif
# ifndef LANG_TIGRINYA
# define LANG_TIGRINYA 0x73
# endif
# ifndef LANG_TSONGA
# define LANG_TSONGA 0x31
# endif
# ifndef LANG_TSWANA
# define LANG_TSWANA 0x32
# endif
# ifndef LANG_TURKMEN
# define LANG_TURKMEN 0x42
# endif
# ifndef LANG_UKRAINIAN
# define LANG_UKRAINIAN 0x22
# endif
# ifndef LANG_URDU
# define LANG_URDU 0x20
# endif
# ifndef LANG_UZBEK
# define LANG_UZBEK 0x43
# endif
# ifndef LANG_VENDA
# define LANG_VENDA 0x33
# endif
# ifndef LANG_VIETNAMESE
# define LANG_VIETNAMESE 0x2a
# endif
# ifndef LANG_WELSH
# define LANG_WELSH 0x52
# endif
# ifndef LANG_XHOSA
# define LANG_XHOSA 0x34
# endif
# ifndef LANG_YI
# define LANG_YI 0x78
# endif
# ifndef LANG_YIDDISH
# define LANG_YIDDISH 0x3d
# endif
# ifndef LANG_YORUBA
# define LANG_YORUBA 0x6a
# endif
# ifndef LANG_ZULU
# define LANG_ZULU 0x35
# endif
# ifndef SUBLANG_ARABIC_SAUDI_ARABIA
# define SUBLANG_ARABIC_SAUDI_ARABIA 0x01
# endif
# ifndef SUBLANG_ARABIC_IRAQ
# define SUBLANG_ARABIC_IRAQ 0x02
# endif
# ifndef SUBLANG_ARABIC_EGYPT
# define SUBLANG_ARABIC_EGYPT 0x03
# endif
# ifndef SUBLANG_ARABIC_LIBYA
# define SUBLANG_ARABIC_LIBYA 0x04
# endif
# ifndef SUBLANG_ARABIC_ALGERIA
# define SUBLANG_ARABIC_ALGERIA 0x05
# endif
# ifndef SUBLANG_ARABIC_MOROCCO
# define SUBLANG_ARABIC_MOROCCO 0x06
# endif
# ifndef SUBLANG_ARABIC_TUNISIA
# define SUBLANG_ARABIC_TUNISIA 0x07
# endif
# ifndef SUBLANG_ARABIC_OMAN
# define SUBLANG_ARABIC_OMAN 0x08
# endif
# ifndef SUBLANG_ARABIC_YEMEN
# define SUBLANG_ARABIC_YEMEN 0x09
# endif
# ifndef SUBLANG_ARABIC_SYRIA
# define SUBLANG_ARABIC_SYRIA 0x0a
# endif
# ifndef SUBLANG_ARABIC_JORDAN
# define SUBLANG_ARABIC_JORDAN 0x0b
# endif
# ifndef SUBLANG_ARABIC_LEBANON
# define SUBLANG_ARABIC_LEBANON 0x0c
# endif
# ifndef SUBLANG_ARABIC_KUWAIT
# define SUBLANG_ARABIC_KUWAIT 0x0d
# endif
# ifndef SUBLANG_ARABIC_UAE
# define SUBLANG_ARABIC_UAE 0x0e
# endif
# ifndef SUBLANG_ARABIC_BAHRAIN
# define SUBLANG_ARABIC_BAHRAIN 0x0f
# endif
# ifndef SUBLANG_ARABIC_QATAR
# define SUBLANG_ARABIC_QATAR 0x10
# endif
# ifndef SUBLANG_AZERI_LATIN
# define SUBLANG_AZERI_LATIN 0x01
# endif
# ifndef SUBLANG_AZERI_CYRILLIC
# define SUBLANG_AZERI_CYRILLIC 0x02
# endif
# ifndef SUBLANG_BENGALI_INDIA
# define SUBLANG_BENGALI_INDIA 0x00
# endif
# ifndef SUBLANG_BENGALI_BANGLADESH
# define SUBLANG_BENGALI_BANGLADESH 0x01
# endif
# ifndef SUBLANG_CHINESE_MACAU
# define SUBLANG_CHINESE_MACAU 0x05
# endif
# ifndef SUBLANG_ENGLISH_SOUTH_AFRICA
# define SUBLANG_ENGLISH_SOUTH_AFRICA 0x07
# endif
# ifndef SUBLANG_ENGLISH_JAMAICA
# define SUBLANG_ENGLISH_JAMAICA 0x08
# endif
# ifndef SUBLANG_ENGLISH_CARIBBEAN
# define SUBLANG_ENGLISH_CARIBBEAN 0x09
# endif
# ifndef SUBLANG_ENGLISH_BELIZE
# define SUBLANG_ENGLISH_BELIZE 0x0a
# endif
# ifndef SUBLANG_ENGLISH_TRINIDAD
# define SUBLANG_ENGLISH_TRINIDAD 0x0b
# endif
# ifndef SUBLANG_ENGLISH_ZIMBABWE
# define SUBLANG_ENGLISH_ZIMBABWE 0x0c
# endif
# ifndef SUBLANG_ENGLISH_PHILIPPINES
# define SUBLANG_ENGLISH_PHILIPPINES 0x0d
# endif
# ifndef SUBLANG_ENGLISH_INDONESIA
# define SUBLANG_ENGLISH_INDONESIA 0x0e
# endif
# ifndef SUBLANG_ENGLISH_HONGKONG
# define SUBLANG_ENGLISH_HONGKONG 0x0f
# endif
# ifndef SUBLANG_ENGLISH_INDIA
# define SUBLANG_ENGLISH_INDIA 0x10
# endif
# ifndef SUBLANG_ENGLISH_MALAYSIA
# define SUBLANG_ENGLISH_MALAYSIA 0x11
# endif
# ifndef SUBLANG_ENGLISH_SINGAPORE
# define SUBLANG_ENGLISH_SINGAPORE 0x12
# endif
# ifndef SUBLANG_FRENCH_LUXEMBOURG
# define SUBLANG_FRENCH_LUXEMBOURG 0x05
# endif
# ifndef SUBLANG_FRENCH_MONACO
# define SUBLANG_FRENCH_MONACO 0x06
# endif
# ifndef SUBLANG_FRENCH_WESTINDIES
# define SUBLANG_FRENCH_WESTINDIES 0x07
# endif
# ifndef SUBLANG_FRENCH_REUNION
# define SUBLANG_FRENCH_REUNION 0x08
# endif
# ifndef SUBLANG_FRENCH_CONGO
# define SUBLANG_FRENCH_CONGO 0x09
# endif
# ifndef SUBLANG_FRENCH_SENEGAL
# define SUBLANG_FRENCH_SENEGAL 0x0a
# endif
# ifndef SUBLANG_FRENCH_CAMEROON
# define SUBLANG_FRENCH_CAMEROON 0x0b
# endif
# ifndef SUBLANG_FRENCH_COTEDIVOIRE
# define SUBLANG_FRENCH_COTEDIVOIRE 0x0c
# endif
# ifndef SUBLANG_FRENCH_MALI
# define SUBLANG_FRENCH_MALI 0x0d
# endif
# ifndef SUBLANG_FRENCH_MOROCCO
# define SUBLANG_FRENCH_MOROCCO 0x0e
# endif
# ifndef SUBLANG_FRENCH_HAITI
# define SUBLANG_FRENCH_HAITI 0x0f
# endif
# ifndef SUBLANG_GERMAN_LUXEMBOURG
# define SUBLANG_GERMAN_LUXEMBOURG 0x04
# endif
# ifndef SUBLANG_GERMAN_LIECHTENSTEIN
# define SUBLANG_GERMAN_LIECHTENSTEIN 0x05
# endif
# ifndef SUBLANG_KASHMIRI_INDIA
# define SUBLANG_KASHMIRI_INDIA 0x02
# endif
# ifndef SUBLANG_MALAY_MALAYSIA
# define SUBLANG_MALAY_MALAYSIA 0x01
# endif
# ifndef SUBLANG_MALAY_BRUNEI_DARUSSALAM
# define SUBLANG_MALAY_BRUNEI_DARUSSALAM 0x02
# endif
# ifndef SUBLANG_NEPALI_INDIA
# define SUBLANG_NEPALI_INDIA 0x02
# endif
# ifndef SUBLANG_PUNJABI_INDIA
# define SUBLANG_PUNJABI_INDIA 0x00
# endif
# ifndef SUBLANG_PUNJABI_PAKISTAN
# define SUBLANG_PUNJABI_PAKISTAN 0x01
# endif
# ifndef SUBLANG_ROMANIAN_ROMANIA
# define SUBLANG_ROMANIAN_ROMANIA 0x00
# endif
# ifndef SUBLANG_ROMANIAN_MOLDOVA
# define SUBLANG_ROMANIAN_MOLDOVA 0x01
# endif
# ifndef SUBLANG_SERBIAN_LATIN
# define SUBLANG_SERBIAN_LATIN 0x02
# endif
# ifndef SUBLANG_SERBIAN_CYRILLIC
# define SUBLANG_SERBIAN_CYRILLIC 0x03
# endif
# ifndef SUBLANG_SINDHI_INDIA
# define SUBLANG_SINDHI_INDIA 0x00
# endif
# ifndef SUBLANG_SINDHI_PAKISTAN
# define SUBLANG_SINDHI_PAKISTAN 0x01
# endif
# ifndef SUBLANG_SPANISH_GUATEMALA
# define SUBLANG_SPANISH_GUATEMALA 0x04
# endif
# ifndef SUBLANG_SPANISH_COSTA_RICA
# define SUBLANG_SPANISH_COSTA_RICA 0x05
# endif
# ifndef SUBLANG_SPANISH_PANAMA
# define SUBLANG_SPANISH_PANAMA 0x06
# endif
# ifndef SUBLANG_SPANISH_DOMINICAN_REPUBLIC
# define SUBLANG_SPANISH_DOMINICAN_REPUBLIC 0x07
# endif
# ifndef SUBLANG_SPANISH_VENEZUELA
# define SUBLANG_SPANISH_VENEZUELA 0x08
# endif
# ifndef SUBLANG_SPANISH_COLOMBIA
# define SUBLANG_SPANISH_COLOMBIA 0x09
# endif
# ifndef SUBLANG_SPANISH_PERU
# define SUBLANG_SPANISH_PERU 0x0a
# endif
# ifndef SUBLANG_SPANISH_ARGENTINA
# define SUBLANG_SPANISH_ARGENTINA 0x0b
# endif
# ifndef SUBLANG_SPANISH_ECUADOR
# define SUBLANG_SPANISH_ECUADOR 0x0c
# endif
# ifndef SUBLANG_SPANISH_CHILE
# define SUBLANG_SPANISH_CHILE 0x0d
# endif
# ifndef SUBLANG_SPANISH_URUGUAY
# define SUBLANG_SPANISH_URUGUAY 0x0e
# endif
# ifndef SUBLANG_SPANISH_PARAGUAY
# define SUBLANG_SPANISH_PARAGUAY 0x0f
# endif
# ifndef SUBLANG_SPANISH_BOLIVIA
# define SUBLANG_SPANISH_BOLIVIA 0x10
# endif
# ifndef SUBLANG_SPANISH_EL_SALVADOR
# define SUBLANG_SPANISH_EL_SALVADOR 0x11
# endif
# ifndef SUBLANG_SPANISH_HONDURAS
# define SUBLANG_SPANISH_HONDURAS 0x12
# endif
# ifndef SUBLANG_SPANISH_NICARAGUA
# define SUBLANG_SPANISH_NICARAGUA 0x13
# endif
# ifndef SUBLANG_SPANISH_PUERTO_RICO
# define SUBLANG_SPANISH_PUERTO_RICO 0x14
# endif
# ifndef SUBLANG_SWEDISH_FINLAND
# define SUBLANG_SWEDISH_FINLAND 0x02
# endif
# ifndef SUBLANG_TAMAZIGHT_ARABIC
# define SUBLANG_TAMAZIGHT_ARABIC 0x01
# endif
# ifndef SUBLANG_TAMAZIGHT_LATIN
# define SUBLANG_TAMAZIGHT_LATIN 0x02
# endif
# ifndef SUBLANG_TIGRINYA_ETHIOPIA
# define SUBLANG_TIGRINYA_ETHIOPIA 0x00
# endif
# ifndef SUBLANG_TIGRINYA_ERITREA
# define SUBLANG_TIGRINYA_ERITREA 0x01
# endif
# ifndef SUBLANG_URDU_PAKISTAN
# define SUBLANG_URDU_PAKISTAN 0x01
# endif
# ifndef SUBLANG_URDU_INDIA
# define SUBLANG_URDU_INDIA 0x02
# endif
# ifndef SUBLANG_UZBEK_LATIN
# define SUBLANG_UZBEK_LATIN 0x01
# endif
# ifndef SUBLANG_UZBEK_CYRILLIC
# define SUBLANG_UZBEK_CYRILLIC 0x02
# endif
#endif

#if defined _LIBC || (defined __GNU_LIBRARY__ && __GNU_LIBRARY__ >= 2)
# define HAVE_LOCALE_NULL
#endif


const char *
_nl_locale_name (int category, const char *categoryname)
{
  const char *retval;

#ifndef WIN32

# if defined HAVE_SETLOCALE && defined HAVE_LC_MESSAGES && defined HAVE_LOCALE_NULL
  retval = setlocale (category, NULL);
# else
  
  retval = getenv ("LC_ALL");
  if (retval == NULL || retval[0] == '\0')
    {
      
      retval = getenv (categoryname);
      if (retval == NULL || retval[0] == '\0')
	{
	  
	  retval = getenv ("LANG");
	  if (retval == NULL || retval[0] == '\0')
	    retval = "C";
	}
    }
# endif

  return retval;

#else 


  LCID lcid;
  LANGID langid;
  int primary, sub;

  retval = getenv ("LC_ALL");
  if (retval != NULL && retval[0] != '\0')
    return retval;
  retval = getenv (categoryname);
  if (retval != NULL && retval[0] != '\0')
    return retval;
  retval = getenv ("LANG");
  if (retval != NULL && retval[0] != '\0')
    return retval;

  
  lcid = GetThreadLocale ();

  
  langid = LANGIDFROMLCID (lcid);

  
  primary = PRIMARYLANGID (langid);
  sub = SUBLANGID (langid);

  switch (primary)
    {
    case LANG_AFRIKAANS: return "af_ZA";
    case LANG_ALBANIAN: return "sq_AL";
    case LANG_AMHARIC: return "am_ET";
    case LANG_ARABIC:
      switch (sub)
	{
	case SUBLANG_ARABIC_SAUDI_ARABIA: return "ar_SA";
	case SUBLANG_ARABIC_IRAQ: return "ar_IQ";
	case SUBLANG_ARABIC_EGYPT: return "ar_EG";
	case SUBLANG_ARABIC_LIBYA: return "ar_LY";
	case SUBLANG_ARABIC_ALGERIA: return "ar_DZ";
	case SUBLANG_ARABIC_MOROCCO: return "ar_MA";
	case SUBLANG_ARABIC_TUNISIA: return "ar_TN";
	case SUBLANG_ARABIC_OMAN: return "ar_OM";
	case SUBLANG_ARABIC_YEMEN: return "ar_YE";
	case SUBLANG_ARABIC_SYRIA: return "ar_SY";
	case SUBLANG_ARABIC_JORDAN: return "ar_JO";
	case SUBLANG_ARABIC_LEBANON: return "ar_LB";
	case SUBLANG_ARABIC_KUWAIT: return "ar_KW";
	case SUBLANG_ARABIC_UAE: return "ar_AE";
	case SUBLANG_ARABIC_BAHRAIN: return "ar_BH";
	case SUBLANG_ARABIC_QATAR: return "ar_QA";
	}
      return "ar";
    case LANG_ARMENIAN: return "hy_AM";
    case LANG_ASSAMESE: return "as_IN";
    case LANG_AZERI:
      switch (sub)
	{
	
	case SUBLANG_AZERI_LATIN: return "az_AZ@latin";
	case SUBLANG_AZERI_CYRILLIC: return "az_AZ@cyrillic";
	}
      return "az";
    case LANG_BASQUE:
      return "eu"; 
    case LANG_BELARUSIAN: return "be_BY";
    case LANG_BENGALI:
      switch (sub)
	{
	case SUBLANG_BENGALI_INDIA: return "bn_IN";
	case SUBLANG_BENGALI_BANGLADESH: return "bn_BD";
	}
      return "bn";
    case LANG_BULGARIAN: return "bg_BG";
    case LANG_BURMESE: return "my_MM";
    case LANG_CAMBODIAN: return "km_KH";
    case LANG_CATALAN: return "ca_ES";
    case LANG_CHEROKEE: return "chr_US";
    case LANG_CHINESE:
      switch (sub)
	{
	case SUBLANG_CHINESE_TRADITIONAL: return "zh_TW";
	case SUBLANG_CHINESE_SIMPLIFIED: return "zh_CN";
	case SUBLANG_CHINESE_HONGKONG: return "zh_HK";
	case SUBLANG_CHINESE_SINGAPORE: return "zh_SG";
	case SUBLANG_CHINESE_MACAU: return "zh_MO";
	}
      return "zh";
    case LANG_CROATIAN:		
      switch (sub)
	{
	case SUBLANG_DEFAULT: return "hr_HR";
	case SUBLANG_SERBIAN_LATIN: return "sr_CS";
	case SUBLANG_SERBIAN_CYRILLIC: return "sr_CS@cyrillic";
	}
      return "hr";
    case LANG_CZECH: return "cs_CZ";
    case LANG_DANISH: return "da_DK";
    case LANG_DIVEHI: return "dv_MV";
    case LANG_DUTCH:
      switch (sub)
	{
	case SUBLANG_DUTCH: return "nl_NL";
	case SUBLANG_DUTCH_BELGIAN:  return "nl_BE";
	}
      return "nl";
    case LANG_EDO: return "bin_NG";
    case LANG_ENGLISH:
      switch (sub)
	{
	case SUBLANG_ENGLISH_US: return "en_US";
	case SUBLANG_ENGLISH_UK: return "en_GB";
	case SUBLANG_ENGLISH_AUS: return "en_AU";
	case SUBLANG_ENGLISH_CAN: return "en_CA";
	case SUBLANG_ENGLISH_NZ: return "en_NZ";
	case SUBLANG_ENGLISH_EIRE: return "en_IE";
	case SUBLANG_ENGLISH_SOUTH_AFRICA: return "en_ZA";
	case SUBLANG_ENGLISH_JAMAICA: return "en_JM";
	case SUBLANG_ENGLISH_CARIBBEAN: return "en_GD"; 
	case SUBLANG_ENGLISH_BELIZE: return "en_BZ";
	case SUBLANG_ENGLISH_TRINIDAD: return "en_TT";
	case SUBLANG_ENGLISH_ZIMBABWE: return "en_ZW";
	case SUBLANG_ENGLISH_PHILIPPINES: return "en_PH";
	case SUBLANG_ENGLISH_INDONESIA: return "en_ID";
	case SUBLANG_ENGLISH_HONGKONG: return "en_HK";
	case SUBLANG_ENGLISH_INDIA: return "en_IN";
	case SUBLANG_ENGLISH_MALAYSIA: return "en_MY";
	case SUBLANG_ENGLISH_SINGAPORE: return "en_SG";
	}
      return "en";
    case LANG_ESTONIAN: return "et_EE";
    case LANG_FAEROESE: return "fo_FO";
    case LANG_FARSI: return "fa_IR";
    case LANG_FINNISH: return "fi_FI";
    case LANG_FRENCH:
      switch (sub)
	{
	case SUBLANG_FRENCH: return "fr_FR";
	case SUBLANG_FRENCH_BELGIAN:  return "fr_BE";
	case SUBLANG_FRENCH_CANADIAN: return "fr_CA";
	case SUBLANG_FRENCH_SWISS: return "fr_CH";
	case SUBLANG_FRENCH_LUXEMBOURG: return "fr_LU";
	case SUBLANG_FRENCH_MONACO: return "fr_MC";
	case SUBLANG_FRENCH_WESTINDIES: return "fr"; 
	case SUBLANG_FRENCH_REUNION: return "fr_RE";
	case SUBLANG_FRENCH_CONGO: return "fr_CG";
	case SUBLANG_FRENCH_SENEGAL: return "fr_SN";
	case SUBLANG_FRENCH_CAMEROON: return "fr_CM";
	case SUBLANG_FRENCH_COTEDIVOIRE: return "fr_CI";
	case SUBLANG_FRENCH_MALI: return "fr_ML";
	case SUBLANG_FRENCH_MOROCCO: return "fr_MA";
	case SUBLANG_FRENCH_HAITI: return "fr_HT";
	}
      return "fr";
    case LANG_FRISIAN: return "fy_NL";
    case LANG_FULFULDE:
      
      return "ff_NG";
    case LANG_GAELIC:
      switch (sub)
	{
	case 0x01:  return "gd_GB";
	case 0x02:  return "ga_IE";
	}
      return "C";
    case LANG_GALICIAN: return "gl_ES";
    case LANG_GEORGIAN: return "ka_GE";
    case LANG_GERMAN:
      switch (sub)
	{
	case SUBLANG_GERMAN: return "de_DE";
	case SUBLANG_GERMAN_SWISS: return "de_CH";
	case SUBLANG_GERMAN_AUSTRIAN: return "de_AT";
	case SUBLANG_GERMAN_LUXEMBOURG: return "de_LU";
	case SUBLANG_GERMAN_LIECHTENSTEIN: return "de_LI";
	}
      return "de";
    case LANG_GREEK: return "el_GR";
    case LANG_GUARANI: return "gn_PY";
    case LANG_GUJARATI: return "gu_IN";
    case LANG_HAUSA: return "ha_NG";
    case LANG_HAWAIIAN:
      return "cpe_US";
    case LANG_HEBREW: return "he_IL";
    case LANG_HINDI: return "hi_IN";
    case LANG_HUNGARIAN: return "hu_HU";
    case LANG_IBIBIO: return "nic_NG";
    case LANG_ICELANDIC: return "is_IS";
    case LANG_IGBO: return "ig_NG";
    case LANG_INDONESIAN: return "id_ID";
    case LANG_INUKTITUT: return "iu_CA";
    case LANG_ITALIAN:
      switch (sub)
	{
	case SUBLANG_ITALIAN: return "it_IT";
	case SUBLANG_ITALIAN_SWISS: return "it_CH";
	}
      return "it";
    case LANG_JAPANESE: return "ja_JP";
    case LANG_KANNADA: return "kn_IN";
    case LANG_KANURI: return "kr_NG";
    case LANG_KASHMIRI:
      switch (sub)
	{
	case SUBLANG_DEFAULT: return "ks_PK";
	case SUBLANG_KASHMIRI_INDIA: return "ks_IN";
	}
      return "ks";
    case LANG_KAZAK: return "kk_KZ";
    case LANG_KONKANI:
      
      return "kok_IN";
    case LANG_KOREAN: return "ko_KR";
    case LANG_KYRGYZ: return "ky_KG";
    case LANG_LAO: return "lo_LA";
    case LANG_LATIN: return "la_VA";
    case LANG_LATVIAN: return "lv_LV";
    case LANG_LITHUANIAN: return "lt_LT";
    case LANG_MACEDONIAN: return "mk_MK";
    case LANG_MALAY:
      switch (sub)
	{
	case SUBLANG_MALAY_MALAYSIA: return "ms_MY";
	case SUBLANG_MALAY_BRUNEI_DARUSSALAM: return "ms_BN";
	}
      return "ms";
    case LANG_MALAYALAM: return "ml_IN";
    case LANG_MALTESE: return "mt_MT";
    case LANG_MANIPURI:
      
      return "mni_IN";
    case LANG_MARATHI: return "mr_IN";
    case LANG_MONGOLIAN:
      return "mn"; 
    case LANG_NEPALI:
      switch (sub)
	{
	case SUBLANG_DEFAULT: return "ne_NP";
	case SUBLANG_NEPALI_INDIA: return "ne_IN";
	}
      return "ne";
    case LANG_NORWEGIAN:
      switch (sub)
	{
	case SUBLANG_NORWEGIAN_BOKMAL: return "no_NO";
	case SUBLANG_NORWEGIAN_NYNORSK: return "nn_NO";
	}
      return "no";
    case LANG_ORIYA: return "or_IN";
    case LANG_OROMO: return "om_ET";
    case LANG_PAPIAMENTU: return "pap_AN";
    case LANG_PASHTO:
      return "ps"; 
    case LANG_POLISH: return "pl_PL";
    case LANG_PORTUGUESE:
      switch (sub)
	{
	case SUBLANG_PORTUGUESE: return "pt_PT";
	case SUBLANG_PORTUGUESE_BRAZILIAN: return "pt_BR";
	}
      return "pt";
    case LANG_PUNJABI:
      switch (sub)
	{
	case SUBLANG_PUNJABI_INDIA: return "pa_IN"; 
	case SUBLANG_PUNJABI_PAKISTAN: return "pa_PK"; 
	}
      return "pa";
    case LANG_RHAETO_ROMANCE: return "rm_CH";
    case LANG_ROMANIAN:
      switch (sub)
	{
	case SUBLANG_ROMANIAN_ROMANIA: return "ro_RO";
	case SUBLANG_ROMANIAN_MOLDOVA: return "ro_MD";
	}
      return "ro";
    case LANG_RUSSIAN:
      return "ru"; 
    case LANG_SAAMI:  return "se_NO";
    case LANG_SANSKRIT: return "sa_IN";
    case LANG_SINDHI:
      switch (sub)
	{
	case SUBLANG_SINDHI_INDIA: return "sd_IN";
	case SUBLANG_SINDHI_PAKISTAN: return "sd_PK";
	}
      return "sd";
    case LANG_SINHALESE: return "si_LK";
    case LANG_SLOVAK: return "sk_SK";
    case LANG_SLOVENIAN: return "sl_SI";
    case LANG_SOMALI: return "so_SO";
    case LANG_SORBIAN:
      
      return "wen_DE";
    case LANG_SPANISH:
      switch (sub)
	{
	case SUBLANG_SPANISH: return "es_ES";
	case SUBLANG_SPANISH_MEXICAN: return "es_MX";
	case SUBLANG_SPANISH_MODERN:
	  return "es_ES@modern";	
	case SUBLANG_SPANISH_GUATEMALA: return "es_GT";
	case SUBLANG_SPANISH_COSTA_RICA: return "es_CR";
	case SUBLANG_SPANISH_PANAMA: return "es_PA";
	case SUBLANG_SPANISH_DOMINICAN_REPUBLIC: return "es_DO";
	case SUBLANG_SPANISH_VENEZUELA: return "es_VE";
	case SUBLANG_SPANISH_COLOMBIA: return "es_CO";
	case SUBLANG_SPANISH_PERU: return "es_PE";
	case SUBLANG_SPANISH_ARGENTINA: return "es_AR";
	case SUBLANG_SPANISH_ECUADOR: return "es_EC";
	case SUBLANG_SPANISH_CHILE: return "es_CL";
	case SUBLANG_SPANISH_URUGUAY: return "es_UY";
	case SUBLANG_SPANISH_PARAGUAY: return "es_PY";
	case SUBLANG_SPANISH_BOLIVIA: return "es_BO";
	case SUBLANG_SPANISH_EL_SALVADOR: return "es_SV";
	case SUBLANG_SPANISH_HONDURAS: return "es_HN";
	case SUBLANG_SPANISH_NICARAGUA: return "es_NI";
	case SUBLANG_SPANISH_PUERTO_RICO: return "es_PR";
	}
      return "es";
    case LANG_SUTU: return "bnt_TZ"; 
    case LANG_SWAHILI: return "sw_KE";
    case LANG_SWEDISH:
      switch (sub)
	{
	case SUBLANG_DEFAULT: return "sv_SE";
	case SUBLANG_SWEDISH_FINLAND: return "sv_FI";
	}
      return "sv";
    case LANG_SYRIAC: return "syr_TR"; 
    case LANG_TAGALOG: return "tl_PH";
    case LANG_TAJIK: return "tg_TJ";
    case LANG_TAMAZIGHT:
      switch (sub)
	{
	
	case SUBLANG_TAMAZIGHT_ARABIC: return "ber_MA@arabic";
	case SUBLANG_TAMAZIGHT_LATIN: return "ber_MA@latin";
	}
      return "ber_MA";
    case LANG_TAMIL:
      return "ta"; 
    case LANG_TATAR: return "tt_RU";
    case LANG_TELUGU: return "te_IN";
    case LANG_THAI: return "th_TH";
    case LANG_TIBETAN: return "bo_CN";
    case LANG_TIGRINYA:
      switch (sub)
	{
	case SUBLANG_TIGRINYA_ETHIOPIA: return "ti_ET";
	case SUBLANG_TIGRINYA_ERITREA: return "ti_ER";
	}
      return "ti";
    case LANG_TSONGA: return "ts_ZA";
    case LANG_TSWANA: return "tn_BW";
    case LANG_TURKISH: return "tr_TR";
    case LANG_TURKMEN: return "tk_TM";
    case LANG_UKRAINIAN: return "uk_UA";
    case LANG_URDU:
      switch (sub)
	{
	case SUBLANG_URDU_PAKISTAN: return "ur_PK";
	case SUBLANG_URDU_INDIA: return "ur_IN";
	}
      return "ur";
    case LANG_UZBEK:
      switch (sub)
	{
	case SUBLANG_UZBEK_LATIN: return "uz_UZ";
	case SUBLANG_UZBEK_CYRILLIC: return "uz_UZ@cyrillic";
	}
      return "uz";
    case LANG_VENDA: return "ve_ZA";
    case LANG_VIETNAMESE: return "vi_VN";
    case LANG_WELSH: return "cy_GB";
    case LANG_XHOSA: return "xh_ZA";
    case LANG_YI: return "sit_CN";
    case LANG_YIDDISH: return "yi_IL";
    case LANG_YORUBA: return "yo_NG";
    case LANG_ZULU: return "zu_ZA";
    default: return "C";
    }

#endif
}
