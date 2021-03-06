 #!/bin/bash

 ./msssdsim -f ../../data/8cass/blktrace_nvme0n1.log -d ../../data/8cass/Freq/nvme0n1/dictionary.log -s 170000000  -r -l 2
 ./msssdsim -f ../../data/8mysql/blktrace_nvme0n1.log -d ../../data/8mysql/Freq/nvme0n1/dictionary.log -s 170000000  -r -l 2
 ./msssdsim -f ../../data/8mysql8cass/blktrace_nvme0n1.log -d ../../data/8mysql8cass/Freq/nvme0n1/dictionary.log -s 170000000  -r -l 2
 ./msssdsim -f ../../data/8cass/blktrace_nvme0n1.log -d ../../data/8cass/Freq/nvme0n1/dictionary.log -s 170000000 -m 16 -c 1 -r -l 2
 ./msssdsim -f ../../data/8mysql/blktrace_nvme0n1.log -d ../../data/8mysql/Freq/nvme0n1/dictionary.log -s 170000000 -m 16 -c 1 -r -l 2
 ./msssdsim -f ../../data/8mysql8cass/blktrace_nvme0n1.log -d ../../data/8mysql8cass/Freq/nvme0n1/dictionary.log -s 170000000 -m 16 -c 1 -r -l 2
 ./msssdsim -f ../../data/8cass/blktrace_nvme0n1.log -d ../../data/8cass/Freq/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/8cass/blktrace_nvme0n1.log -d ../../data/8cass/Seq/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/8cass/blktrace_nvme0n1.log -d ../../data/8cass/Rec/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/8cass/blktrace_nvme0n1.log -d ../../data/8cass/Coh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/8cass/blktrace_nvme0n1.log -d ../../data/8cass/FreqSeq/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/8cass/blktrace_nvme0n1.log -d ../../data/8cass/FreqRec/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/8cass/blktrace_nvme0n1.log -d ../../data/8cass/FreqCoh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/8cass/blktrace_nvme0n1.log -d ../../data/8cass/SeqRec/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/8cass/blktrace_nvme0n1.log -d ../../data/8cass/SeqCoh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/8cass/blktrace_nvme0n1.log -d ../../data/8cass/RecCoh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/8cass/blktrace_nvme0n1.log -d ../../data/8cass/FreqSeqRec/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/8cass/blktrace_nvme0n1.log -d ../../data/8cass/FreqRecCoh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/8cass/blktrace_nvme0n1.log -d ../../data/8cass/FreqSeqCoh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/8cass/blktrace_nvme0n1.log -d ../../data/8cass/SeqRecCoh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/8cass/blktrace_nvme0n1.log -d ../../data/8cass/FreqSeqRecCoh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/8mysql/blktrace_nvme0n1.log -d ../../data/8mysql/Freq/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/8mysql/blktrace_nvme0n1.log -d ../../data/8mysql/Seq/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/8mysql/blktrace_nvme0n1.log -d ../../data/8mysql/Rec/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/8mysql/blktrace_nvme0n1.log -d ../../data/8mysql/Coh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/8mysql/blktrace_nvme0n1.log -d ../../data/8mysql/FreqSeq/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/8mysql/blktrace_nvme0n1.log -d ../../data/8mysql/FreqRec/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/8mysql/blktrace_nvme0n1.log -d ../../data/8mysql/FreqCoh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/8mysql/blktrace_nvme0n1.log -d ../../data/8mysql/SeqRec/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/8mysql/blktrace_nvme0n1.log -d ../../data/8mysql/SeqCoh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/8mysql/blktrace_nvme0n1.log -d ../../data/8mysql/RecCoh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/8mysql/blktrace_nvme0n1.log -d ../../data/8mysql/FreqSeqRec/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/8mysql/blktrace_nvme0n1.log -d ../../data/8mysql/FreqRecCoh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/8mysql/blktrace_nvme0n1.log -d ../../data/8mysql/FreqSeqCoh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/8mysql/blktrace_nvme0n1.log -d ../../data/8mysql/SeqRecCoh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/8mysql/blktrace_nvme0n1.log -d ../../data/8mysql/FreqSeqRecCoh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/8mysql8cass/blktrace_nvme0n1.log -d ../../data/8mysql8cass/Freq/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/8mysql8cass/blktrace_nvme0n1.log -d ../../data/8mysql8cass/Seq/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/8mysql8cass/blktrace_nvme0n1.log -d ../../data/8mysql8cass/Rec/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/8mysql8cass/blktrace_nvme0n1.log -d ../../data/8mysql8cass/Coh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/8mysql8cass/blktrace_nvme0n1.log -d ../../data/8mysql8cass/FreqSeq/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/8mysql8cass/blktrace_nvme0n1.log -d ../../data/8mysql8cass/FreqRec/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/8mysql8cass/blktrace_nvme0n1.log -d ../../data/8mysql8cass/FreqCoh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/8mysql8cass/blktrace_nvme0n1.log -d ../../data/8mysql8cass/SeqRec/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/8mysql8cass/blktrace_nvme0n1.log -d ../../data/8mysql8cass/SeqCoh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/8mysql8cass/blktrace_nvme0n1.log -d ../../data/8mysql8cass/RecCoh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/8mysql8cass/blktrace_nvme0n1.log -d ../../data/8mysql8cass/FreqSeqRec/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/8mysql8cass/blktrace_nvme0n1.log -d ../../data/8mysql8cass/FreqRecCoh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/8mysql8cass/blktrace_nvme0n1.log -d ../../data/8mysql8cass/FreqSeqCoh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/8mysql8cass/blktrace_nvme0n1.log -d ../../data/8mysql8cass/SeqRecCoh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/8mysql8cass/blktrace_nvme0n1.log -d ../../data/8mysql8cass/FreqSeqRecCoh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/1cass/blktrace_nvme0n1.log -d ../../data/8cass/Freq/nvme0n1/dictionary.log -s 170000000  -r -l 2
 ./msssdsim -f ../../data/1mysql/blktrace_nvme0n1.log -d ../../data/8mysql/Freq/nvme0n1/dictionary.log -s 170000000  -r -l 2
 ./msssdsim -f ../../data/1mysql1cass/blktrace_nvme0n1.log -d ../../data/8mysql8cass/Freq/nvme0n1/dictionary.log -s 170000000  -r -l 2
 ./msssdsim -f ../../data/1cass/blktrace_nvme0n1.log -d ../../data/8cass/Freq/nvme0n1/dictionary.log -s 170000000 -m 16 -c 1 -r -l 2
 ./msssdsim -f ../../data/1mysql/blktrace_nvme0n1.log -d ../../data/8mysql/Freq/nvme0n1/dictionary.log -s 170000000 -m 16 -c 1 -r -l 2
 ./msssdsim -f ../../data/1mysql1cass/blktrace_nvme0n1.log -d ../../data/8mysql8cass/Freq/nvme0n1/dictionary.log -s 170000000 -m 16 -c 1 -r -l 2
 ./msssdsim -f ../../data/1cass/blktrace_nvme0n1.log -d ../../data/8cass/Freq/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/1cass/blktrace_nvme0n1.log -d ../../data/8cass/Seq/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/1cass/blktrace_nvme0n1.log -d ../../data/8cass/Rec/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/1cass/blktrace_nvme0n1.log -d ../../data/8cass/Coh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/1cass/blktrace_nvme0n1.log -d ../../data/8cass/FreqSeq/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/1cass/blktrace_nvme0n1.log -d ../../data/8cass/FreqRec/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/1cass/blktrace_nvme0n1.log -d ../../data/8cass/FreqCoh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/1cass/blktrace_nvme0n1.log -d ../../data/8cass/SeqRec/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/1cass/blktrace_nvme0n1.log -d ../../data/8cass/SeqCoh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/1cass/blktrace_nvme0n1.log -d ../../data/8cass/RecCoh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/1cass/blktrace_nvme0n1.log -d ../../data/8cass/FreqSeqRec/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/1cass/blktrace_nvme0n1.log -d ../../data/8cass/FreqRecCoh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/1cass/blktrace_nvme0n1.log -d ../../data/8cass/FreqSeqCoh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/1cass/blktrace_nvme0n1.log -d ../../data/8cass/SeqRecCoh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/1cass/blktrace_nvme0n1.log -d ../../data/8cass/FreqSeqRecCoh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/1mysql/blktrace_nvme0n1.log -d ../../data/8mysql/Freq/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/1mysql/blktrace_nvme0n1.log -d ../../data/8mysql/Seq/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/1mysql/blktrace_nvme0n1.log -d ../../data/8mysql/Rec/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/1mysql/blktrace_nvme0n1.log -d ../../data/8mysql/Coh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/1mysql/blktrace_nvme0n1.log -d ../../data/8mysql/FreqSeq/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/1mysql/blktrace_nvme0n1.log -d ../../data/8mysql/FreqRec/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/1mysql/blktrace_nvme0n1.log -d ../../data/8mysql/FreqCoh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/1mysql/blktrace_nvme0n1.log -d ../../data/8mysql/SeqRec/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/1mysql/blktrace_nvme0n1.log -d ../../data/8mysql/SeqCoh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/1mysql/blktrace_nvme0n1.log -d ../../data/8mysql/RecCoh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/1mysql/blktrace_nvme0n1.log -d ../../data/8mysql/FreqSeqRec/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/1mysql/blktrace_nvme0n1.log -d ../../data/8mysql/FreqRecCoh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/1mysql/blktrace_nvme0n1.log -d ../../data/8mysql/FreqSeqCoh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/1mysql/blktrace_nvme0n1.log -d ../../data/8mysql/SeqRecCoh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/1mysql/blktrace_nvme0n1.log -d ../../data/8mysql/FreqSeqRecCoh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/1mysql1cass/blktrace_nvme0n1.log -d ../../data/8mysql8cass/Freq/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/1mysql1cass/blktrace_nvme0n1.log -d ../../data/8mysql8cass/Seq/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/1mysql1cass/blktrace_nvme0n1.log -d ../../data/8mysql8cass/Rec/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/1mysql1cass/blktrace_nvme0n1.log -d ../../data/8mysql8cass/Coh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/1mysql1cass/blktrace_nvme0n1.log -d ../../data/8mysql8cass/FreqSeq/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/1mysql1cass/blktrace_nvme0n1.log -d ../../data/8mysql8cass/FreqRec/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/1mysql1cass/blktrace_nvme0n1.log -d ../../data/8mysql8cass/FreqCoh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/1mysql1cass/blktrace_nvme0n1.log -d ../../data/8mysql8cass/SeqRec/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/1mysql1cass/blktrace_nvme0n1.log -d ../../data/8mysql8cass/SeqCoh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/1mysql1cass/blktrace_nvme0n1.log -d ../../data/8mysql8cass/RecCoh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/1mysql1cass/blktrace_nvme0n1.log -d ../../data/8mysql8cass/FreqSeqRec/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/1mysql1cass/blktrace_nvme0n1.log -d ../../data/8mysql8cass/FreqRecCoh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/1mysql1cass/blktrace_nvme0n1.log -d ../../data/8mysql8cass/FreqSeqCoh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/1mysql1cass/blktrace_nvme0n1.log -d ../../data/8mysql8cass/SeqRecCoh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
 ./msssdsim -f ../../data/1mysql1cass/blktrace_nvme0n1.log -d ../../data/8mysql8cass/FreqSeqRecCoh/nvme0n1/dictionary.log -s 170000000 -m 16 -c 4 -r -l 2
