// silhouettes.h
// Header file.

/// begin of DEBUG VARIABLES part ///
/* The switcher for writing main-debug messages to console.
 *  [d:] in console log.
 */
bool debug = false;

/* The switcher for writing to console
 *  number of every pixel that checking now.
 *  [cp:] in console log.
 */
bool currentPixel_debug = false;

/* The switcher for writing to console
 *  number of every pixel that checking now
 *  in recursive calls.
 *  [cpr:] in console log.
 */
bool currentPixelRecursive_debug = false;

/* The switcher for creating [silhouettes.txt] file.
 * The binary pixel array will be placed into this file.
 * [cf:] in console log.
 */
bool createFile_debug = false;

/* The switcher for writing to console
 *  information about pixel where
 *  silhouette was found.
 *  [sf:] in console log.
 */
bool silhouetteFounder_debug = true;
/// end of DEBUG VARIABLES part ///

/// start of SEARCHER SETTINGS VARIABLES part ///
/* Shilouette minimum size
 * Due to the fact that this method recognizes all non-white pixels
 *  and the method of contrasting the image is not ideal,
 *  we can get some small separate "islands" of unnecessary pixels.
 *
 * This parameter specifies the size of the "Islands"
 *  which we will dont calculate.
 *
 * Default: 0.005 (in %/100)
 * The program automaticly calculate this value
 *  based on the size of the picture.
 *
 */
double MINIMUM_SILHOUETTE_SIZE = 0.005;

/* Lightness factor:
 * Only for "First binarization method."
 * Set > 128 to recognize lighter shades of gray.
 * Set < 128 to recognize darker shades of gray.
 * Default: 128.
 *
 * This is necessary to filter out different distortion,
 *  noises, watermarks in the image.
 */
int LIGHTNESS = 128;
/// end of SEARCHER SETTINGS VARIABLES part ///

