add_executable (gcx
aggregatefunctavgexpression.cpp         constexpression.cpp          orcondexpression.cpp                    projectiontreelabel.cpp
aggregatefunctcountexpression.cpp       dependencyset.cpp            parvarmap.cpp                           projectiontreelabels.cpp
aggregatefunctexpression.cpp            dependencytuple.cpp          passiveprojectiontree.cpp               projectiontreenode.cpp
aggregatefunctlistexpression.cpp        emptyexpression.cpp          passiveprojectiontreeconfiguration.cpp  role.cpp
aggregatefunctmaxexpression.cpp         environment.cpp              passiveprojectiontreenode.cpp           rolelist.cpp
aggregatefunctminexpression.cpp         error.cpp                    pathenvironment.cpp                     sequenceexpression.cpp
aggregatefunctstddevpopexpression.cpp   executor.cpp                 pathexpression.cpp                      signoffexpression.cpp
aggregatefunctstddevsampexpression.cpp  existscondexpression.cpp     pathexpressionadornment.cpp             streampreprocessor.cpp
aggregatefunctsumexpression.cpp         expression.cpp               pathstepattribute.cpp                   streamtracker.cpp
aggregatefunctvarpopexpression.cpp      falsecondexpression.cpp      pathstepattributeposition.cpp           stringhash.cpp
aggregatefunctvarsampexpression.cpp     forexpression.cpp            pathstepexpression.cpp                  tagmap.cpp
andcondexpression.cpp                   fsamap.cpp                   pathstepnodeexpression.cpp              tagnode.cpp
buffer.cpp                              ifexpression.cpp             pathstepstarexpression.cpp              tokenconfiguration.cpp
bufferiterator.cpp                      intmultiset.cpp              pathsteptagexpression.cpp               truecondexpression.cpp
buffernode.cpp                          loader.cpp                   pathsteptextexpression.cpp              typeenums.cpp
buffernodelist.cpp                      main.cpp                     prettyprint.cpp                         varexpression.cpp
charnode.cpp                            miscfunctions.cpp            projectiondfa.cpp                       variabletree.cpp
cmdline.cpp                             nodeconstructexpression.cpp  projectiondfastate.cpp                  variabletreenode.cpp
condexpression.cpp                      notcondexpression.cpp        projectiondfatransitions.cpp            varname.cpp
condoperandexpression.cpp               operandexpression.cpp        projectiontree.cpp                      varstepexpression.cpp



query_lexer.C  query_parser.C  sax.C
)


install(TARGETS gcx DESTINATION bin)

