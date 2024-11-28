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

void SetStyle()
{
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(57);
  gStyle->SetOptTitle(0);
}

TGraphErrors *graph;

void fit()
{
  graph = new TGraphErrors("Dati_calibrazione.txt", "%lg %lg %lg %lg");
  graph->SetTitle("Retta di calibrazione");

  graph->SetMarkerStyle(20);
  graph->SetMarkerSize(1);
  graph->SetMarkerColor(kBlack);

  graph->Draw("APE");
  graph->GetXaxis()->SetLimits(0, 900);
  graph->GetYaxis()->SetLimits(0, 850);
  graph->GetXaxis()->SetTitle("Multimetro (mV)");
  graph->GetYaxis()->SetTitle("Oscilloscopio (mV)");

  TF1 *f1 = new TF1("f1", "[0] + [1]*x", 0, 900);

  f1->SetParameters(0, 1);
  f1->SetParName(0, "q");
  f1->SetParName(1, "m");
  f1->SetLineColor(kGreen + 3); // Colore linea verde scuro
  f1->SetLineWidth(2);          // Spessore linea

  graph->Fit("f1", "R");
  gStyle->SetOptFit(1011);

  // Creazione della legenda
  TLegend *legend = new TLegend(0.15, 0.75, 0.45, 0.85); // Posizione (x1, y1, x2, y2)
  legend->SetBorderSize(0);                              // Rimuove il bordo
  legend->SetFillStyle(0);                               // Rimuove il riempimento
  legend->AddEntry(graph, "Punti sperimentali", "p");    // "p" per i punti
  legend->AddEntry(f1, "Linea del fit", "l");            // "l" per la linea
  legend->Draw();
}