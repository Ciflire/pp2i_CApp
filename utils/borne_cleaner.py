import pandas as pd
import matplotlib.pyplot as plt


def main():
  # Reads data, deletes duplicates and saves it
  bornes = pd.read_csv('data/borne_firststep.csv', sep=',').drop_duplicates()

  # Export to csv
  bornes.to_csv('data/borne_cleaned.csv', sep=',', index=False)

  # Plot
  plt.figure(0, figsize=[50, 50])
  plt.scatter(bornes['consolidated_longitude'], bornes['consolidated_latitude'],
            s=bornes['nbre_pdc'].values*10, c=bornes['puissance_nominale'].values, cmap='plasma')
  plt.savefig('data/borne_cleaned.png')
  
if __name__ == '__main__':
  main()