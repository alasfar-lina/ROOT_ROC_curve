
#include "TH1F.h"
#include "TGraph"
TGraph RocCurve( TH1F sigHist, TH1F bkgHist ) {
// if sigHist is a TH1F* and bkgHist is a TH1F* (with the same number of bins!)
int nbins = sigHist->GetNbinsX();

// get the total integrals for each histogram
float sig_integral = sigHist->Integral(1,nbins);
float bkg_integral = bkgHist->Integral(1,nbins);

// create containers sig = x points, bkg = y points
std::vector<float> sigPoints(nbins);
std::vector<float> bkgPoints(nbins);

// in the loop, fill the containers with the x and y points
// each x point is this loop's slice integral over total integral (signal)
// each y point is this loop's slice integral over total integral (background)
for ( int i = 0; i < nbins; ++i ) {
  // notice the slice integral is dependent on i!
  // on each iteration we take a larger and larger slice of the histograms
  // eventually the slice will be the total integral (from bin 1 to bin nbins)
  // that point is (1,1) on the ROC curve.
  float sig_slice_integral = sigHist->Integral(nbins-i,nbins);
  float bkg_slice_integral = bkgHist->Integral(nbins-i,nbins);
  sigPoints.push_back(sig_slice_integral/sig_integral);
  bkgPoints.push_back(bkg_slice_integral/bkg_integral);
}

// create a TGraph from the containers
// this graph will have N (=nbins) number of points forming the curve.
TGraph *g = new TGraph(sigPoints.size(),&sigPoints[0],&bkgPoints[0]);

return g;
}
