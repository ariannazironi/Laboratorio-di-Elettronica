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
TCanvas* c1;

void fit(){
    graph = new TGraphErrors("Dati_-200.txt", "%lg %lg %lg %lg");
    graph->SetTitle("I_B = 200 mA");
    c1 = new TCanvas("c1");
    
    graph->SetMarkerStyle(4);
    graph->Draw("AP");

    c1->SetGrid();
    graph->GetXaxis()->SetTitle("Tensione (-V)");
    graph->GetYaxis()->SetTitle("Corrente (-mA)");

    TF1 *f1 = new TF1("f1", "(x - [0])/[1]", 1 , 4);

    f1->SetParameters(0.2, 10);
    f1->SetParName(0, "a");
    f1->SetParName(1, "b");

    graph->Fit("f1", "R");
    gStyle->SetOptFit(1111);
}