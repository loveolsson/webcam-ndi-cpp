export interface ValueInfoOption {
  [index: string]: string;
}

export interface ValueInfo {
  numInt?: number;
  minInt?: number;
  maxInt?: number;
  numFloat?: number;
  minFloat?: number;
  maxFloat?: number;
  str?: string;
  opt?: ValueInfoOption;
}