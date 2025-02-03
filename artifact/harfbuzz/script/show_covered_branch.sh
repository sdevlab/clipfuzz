RUNNER=$1
COV_DATA=$2
EXPORT_ANLAYSIS=$3

llvm-cov-12 export $RUNNER -instr-profile=$COV_DATA > temp.export

covered_branches=$(python3 $EXPORT_ANLAYSIS temp.export)

echo "$(basename $COV_DATA) (Covered Branches) $covered_branches"
