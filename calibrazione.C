#include <cmath> 
#include <iostream> 

#include "TCanvas.h" 
#include "TF1.h" 
#include "TFile.h" 
#include "TFitResult.h" 
#include "TH1F.h" 
#include "TLegend.h" 
#include "TMath.h" 
#include "TMatrixD.h" 
#include "TROOT.h" 
#include "TRandom.h" 
#include "TStyle.h" 
#include "TGraphErrors.h"

void SetStyle(){
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(57);
  gStyle->SetOptTitle(0);
}

TGraphErrors* graph;

void fit(){
    graph = new TGraphErrors("Dati_calibrazione.txt", "%lg %lg %lg %lg");
    graph->SetTitle("Retta di calibrazione");

    graph->SetMarkerStyle(4);
    graph->Draw("AP");
    graph->GetXaxis()->SetLimits(0, 900);
    graph->GetYaxis()->SetLimits(0, 850);
    graph->GetXaxis()->SetTitle("Multimetro (mV)");
    graph->GetYaxis()->SetTitle("Oscilloscopio (mV)");
    
    TF1 *f1 = new TF1("f1", "[0] + [1]*x", 0, 900);

    f1->SetParameters(0, 1);
    f1->SetParName(0, "q");
    f1->SetParName(1, "m");
    
    graph->Fit("f1", "R");
    gStyle->SetOptFit(1111);
}