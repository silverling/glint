import sys
from fontTools import ttLib

if len(sys.argv) < 2:
    print("Get the glyph unicode ranges of font.", end="\n\n")
    print(f"Usage: {sys.argv[0]} <font.ttf | font.otf>")
    exit(0)

font = ttLib.TTFont(sys.argv[1])
cmap_table = font["cmap"]

# Get the best Unicode subtable (usually platformID 3, encodingID 1 or 10)
unicode_cmap = cmap_table.getBestCmap()
codepoints = sorted(unicode_cmap.keys())  # Get the list of Unicode code points


# Convert codepoints into ranges
def codepoints_to_ranges(codepoints):
    ranges = []
    start = prev = codepoints[0]
    for cp in codepoints[1:]:
        if cp == prev + 1:
            prev = cp
        else:
            ranges.append((start, prev))
            start = prev = cp
    ranges.append((start, prev))
    return ranges


# Print as ranges
for start, end in codepoints_to_ranges(codepoints):
    print(f"0x{start:04X}, 0x{end:04X},")
